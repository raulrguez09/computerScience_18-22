/**************************************************************************************/
/***************************** Práctica 4: Node.js ************************************/
/********************* Desarrollo de sistemas distribuidos ****************************/
/*************************** Raúl Rodríguez Pérez DS2 *********************************/
/**************************************************************************************/

// Añadimos los módulos a Node.js
var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};
var MongoClient = require('mongodb').MongoClient;

// Valores los sensores
var luminosidad = 10;
var temperatura = 25;
var humedad = 50;
var viento;

// Valores min y max de los sensores
var temp_max = 30;
var temp_min = 10;
var lumi_max = 20;
var lumi_min = 5;  
var hum_max = 25;
var hum_min = 5;
var viento_max = 10;
var viento_min = 2;

// Variables de los actuadores (básicos)
var agenteDomotico = true;
var persiana = false;
var aireAcondicionado = false;

// Variables de los actuadores (extras)
var calefaccion = false;
var humidificador = false;
var ventana = true;


function agente(){
	var respuestas = Array();

	if(agenteDomotico){
		// Respuestas para la temperatura alta (actuador: aireAcondicionado)
		if (temperatura > temp_max && !aireAcondicionado){
			aireAcondicionado = true;
			respuestas.push("La temperatura ha superado el valor máx permitido, el agente ha encendido el aire acondicionado\n");
			
			if(calefaccion){
				calefaccion = false;
				respuestas.push("El agente ha apagado la calefacción ya que no es necesaria \n");
			}

			if(!humidificador){
				humidificador = false;
				respuestas.push("El agente ha encendido el humidificador porque el aire acondicionado se ha encendido \n");
			}
				
		}else if (temperatura < temp_max && temperatura > temp_min && aireAcondicionado){
			aireAcondicionado = false;
			respuestas.push("El agente ha apagado el aire acondicionado porque la temperatura actual es óptima \n");
		}
		
		// Respuestas para la temperatura baja (actuador: calefacción)
		if(temperatura < temp_min && !calefaccion){
			calefaccion = true;
			respuestas.push("La temperatura ha superado el valor min permitido, el agente ha encendido la calefacción\n")
			
			if(aireAcondicionado){
				aireAcondicionado = false;
				respuestas.push("El agente ha apagado el aire acondicionado ya que no es necesario \n");
			}

			if(humidificador){
				humidificador = false;
				respuestas.push("El agente ha apagado el humidificador ya que no es necesario \n");
			}
				
		}else if (temperatura < temp_max && temperatura > temp_min && calefaccion){
			calefaccion = false;
			respuestas.push("El agente ha apagado la calefacción porque la temperatura actual es óptima \n")
		}

		// Respuestas para mucho viento (actuador: ventana)
		if(viento > viento_max && ventana){
			ventana = false;
			respuestas.push("El viento ha superado el valor máx permitido, el agente ha cerrado la ventana \n");
		}

		if((aireAcondicionado | calefaccion) && ventana){
			ventana = false;
			respuestas.push("Hay algun dispositivo regulador de temperatura en uso, el agente ha cerrado la ventana \n");

		}else if (!aireAcondicionado && !calefaccion && !ventana && viento < viento_min){
			ventana = true;
			respuestas.push("El agente ha abierto la ventana porque no hay ningún dispositivo de control de temperatura en uso y el viento es mínimo \n");
		}

		//Respuestar para luminosidad alta/baja (actuador: persiana)
		if (luminosidad > lumi_max && persiana){
			respuestas.push("La luminosidad ha superado el valor max permitido, el agente ha bajado la persiana \n");
			persiana = false;
		}

		if (luminosidad < lumi_min && !persiana){
			respuestas.push("La luminosidad ha superado el valor min permitido, el agente ha subido la persiana \n");
			persiana = true;
		}

		// Respuestas para humedad alta/baja (actuador: humidificador)
		if(humedad < hum_min && !humidificador){
			humidificador = true;
			respuestas.push("Los niveles de humedad están por debajo del min permitido, el agente ha encendido el humidificador \n");
		} 
		
		if(humedad > hum_max && humidificador){
			humidificador = false;
			respuestas.push("Los niveles de humedad están por encima del max permitido, el agente ha encendido el humidificador \n");
		}

	}else{
		respuestas.push("El agente domótico esta apagado, no puede realizar sus funciones \n");
	}
		return respuestas;
}

var httpServer = http.createServer(
	function(request, response) {
		var uri = url.parse(request.url).pathname;
		if (uri=="/"){
			uri = "/sensores.html";
		}
		var fname = path.join(process.cwd(), uri);
		
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write('Error: Fallo en la lectura del fichero: '+uri);
						response.end();
					}
				});
			}
			else{
				console.log("Peticion invalida: "+uri);
				response.writeHead(200, {"Content-Type": "text/plain"});
				response.write('404 Not Found\n');
				response.end();
			}
		});		
	});


MongoClient.connect("mongodb://localhost:27017/", {useNewUrlParser: true, useUnifiedTopology: true},function(err, db){
	httpServer.listen(8080);
	console.log("El servicio HTTP se ha iniciado");
	var io = socketio(httpServer);
	var users = new Array();
	var dbo = db.db("pruebaBD");

	// Borrar los datos para actualizarla
	dbo.collection("datos").deleteMany({});

	dbo.createCollection("datos", function(err, collection){
		io.sockets.on('connection', function(client){
			//añadimos al array de usuarios información del nuevo usuario que se ha conectado para mostrarla a posteriori
			users.push({address:client.request.connection.remoteAddress, port:client.request.connection.remotePort});		
			//Actualizamos el registro de modificaciones
			obtenerRegistro();

			//Emitimos el array de usuarios activos
			io.emit('usuariosActivos', users);

			// Emitimos los valores de los diferentes sensores junto a las repsuestas del agente
			client.emit('valorSensores', {
				temperatura: temperatura,
				luminosidad: luminosidad,
				humedad: humedad,
				viento: viento,
				estadoAireAcondicionado: aireAcondicionado,
				estadoPersiana: persiana,
				estadoAgenteDomotico: agenteDomotico,
				estadoCalefaccion: calefaccion,
				estadoVentana: ventana,
				estadoHumidificador: humidificador,
				respuestasAgente : ''
			});

			// Método que escucha la petición de apagar el aire acondicionado
			client.on('aireAcondicionado',function(){
				aireAcondicionado = !aireAcondicionado;
				var respuesta;
				if(aireAcondicionado){
					respuesta = 'El usuario ha encendido el aire acondicionado de manera manual'
				}
				else {
					respuesta = 'El usuario ha apagado el aire acondicionado de manera manual'
				}
				// Actualizamos los valores que han sido modificados por los usuarios
				actualizarValoresUsuarios(respuesta);
				// Dejamos constancia de esas modificaciones en el registro
				obtenerRegistro();
			})

			// Método que escucha la petición de cerrar la persiana
			client.on('persiana',function(){
				persiana = !persiana;
				if(persiana){ 
					respuesta = 'El usuario ha subido la persiana de manera manual' 
				}else{ 
					respuesta = 'El usuario ha bajado la persiana de manera manual'
				}
				// Actualizamos los valores que han sido modificados por los usuarios
				actualizarValoresUsuarios(respuesta);
				// Dejamos constancia de esas modificaciones en el registro
				obtenerRegistro() 
			})

			// Método que escucha la petición de cerrar la ventana
			client.on('ventana',function(){
				ventana = !ventana;
				if(ventana){
					respuesta = 'El usuario ha abierto la ventana de manera manual' 
				}else{ 
					respuesta = 'El usuario ha cerrado la ventana de manera manual'
				}
				// Actualizamos los valores que han sido modificados por los usuarios				
				actualizarValoresUsuarios(respuesta);
				// Dejamos constancia de esas modificaciones en el registro
				obtenerRegistro();
			})

			// Método que escucha la petición de apagar el humidificador
			client.on('humidificador',function(){
				humidificador = !humidificador;
				if(humidificador){
					respuesta = 'El usuario ha encendido el humidificador de manera manual' 
				}else{
					respuesta = 'El usuario ha apagado el humidificador de manera manual'
				}
				// Actualizamos los valores que han sido modificados por los usuarios
				actualizarValoresUsuarios(respuesta);
				// Dejamos constancia de esas modificaciones en el registro
				obtenerRegistro() 
			})

			// Método que escucha la petición de apagar la calefaccion
			client.on('calefaccion',function(){
				calefaccion = !calefaccion;
				if(calefaccion){ 
					respuesta = 'El usuario ha encendido la calefacción de manera manual' 
				}else{
					respuesta = 'El usuario ha apagado la calefacción de manera manual'
				}
				// Actualizamos los valores que han sido modificados por los usuarios
				actualizarValoresUsuarios(respuesta);
				// Dejamos constancia de esas modificaciones en el registro
				obtenerRegistro() 
			})

			// Método que escucha la petición de apagar al agente
			client.on('estadoAgente',function(){
				agenteDomotico = !agenteDomotico;
				var respuestas = agente();
				// Actualizamos los valores que han sido modificados por los usuarios
				actualizarValoresUsuarios(respuestas);
			})

			// Método que obtiene los valores que se añaden el el input de sensores
			client.on('valoresCaptados',function(data){
				if(data.sensor == 'temperatura'){
					temperatura = data.valor;

				}else if(data.sensor == 'luminosidad'){
					luminosidad = data.valor;

				}else if(data.sensor == 'humedad'){
					humedad = data.valor;
				}

				var respuestas = agente();
				actualizarValoresUsuarios(respuestas);
				dbo.collection("datos").insertOne(data, {safe:true}, function(err, result) {});
				obtenerRegistro()
			})
			
			// Método que escucha la petición de mandar el registro de modificaciones
			client.on('obtenerRegistro',function(){
				obtenerRegistro();
			});

			// Método para obtener el registro de modificaciones
			function obtenerRegistro(){
				dbo.collection("datos").find().toArray(function(err, results){
					io.emit('obtenerRegistro',results);
				});
			}
		});

		// Método para actualizar los valores de los sensores cambiados por los usuarios
		function actualizarValoresUsuarios(respuestas){
			io.sockets.emit('valorSensores', {
				temperatura: temperatura,
				luminosidad: luminosidad,
				humedad: humedad,
				viento: viento,
				estadoAireAcondicionado: aireAcondicionado,
				estadoPersiana: persiana,
				estadoAgenteDomotico: agenteDomotico,
				estadoCalefaccion: calefaccion,
				estadoVentana: ventana,
				estadoHumidificador: humidificador,
				respuestasAgente : respuestas
			});
		}

		/**********************************************************************/
		/********** Sección para establecer conexión con OpenWeather **********/
		/********* Obtenemos la velocidad del viento actual en Granada ********/
		/**********************************************************************/

		// Cargamos el paquete request
		const request = require('request');

		// Definimos nuestra API KEY
		let apiKey = '18538accdec0043e3fb33f8b57c21613';
		let ciudad = 'Granada';
		let unidad = 'metric';
		let url = `http://api.openweathermap.org/data/2.5/weather?q=${ciudad}&appid=${apiKey}&units=${unidad}`

		// A request le pasamos una url, una función de callback con 3 argumentos: err, response y body
		request(url, function (err, response, body) {
			// Comprobamos si hay algún error en la petición. Si hay errores, hacemos un log del error.
			// Si no hay errores, hacemos un log de toda la respuesta obtenida en la petición.
			if(err){
				console.log('error:', error);
			} else {

				let info= JSON.parse(body);
				viento = info.wind.speed;
			}
		});

	});

});

	


