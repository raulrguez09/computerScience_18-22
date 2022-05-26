function mostrar() {
    div = document.getElementById("show");
    console.log(div);
    if(div.style.display == ''){
        div.style.display = 'none';
        document.getElementById("mostrar").innerText = "Mostrar comentarios";
        console.log(div);
    }
    else{
        div.style.display = '';
        document.getElementById("mostrar").innerText = "Ocultar comentarios";
        console.log(div);
    }
}

function validarEmail(mail){
    if(!(/^([\da-z_\.-]+)@([\da-z\.-]+)\.([a-z\.]{2,6})$/.test(mail))){
        alert("La direccion de email no es valida.");
        return false;
    }
    else{
        return true;
    }
}

function ponerComentario(){
    var comentario = document.getElementById("a");

    var nombre = document.getElementById("nombre").value;
    var mail = document.getElementById("mail").value;
    var mensaje = document.getElementById("msg").value;

    if(nombre == "" || mail == "" || mensaje == ""){
        alert("Es obligatorio rellenar todos los campos.");
        return false;
    }
    else{
        if(!validarEmail(mail))
        return false;
    }
    var fecha = new Date();
    fecha.setMonth(fecha.getMonth()+1);

    var nuevo = '<p id>'+ '<b>' + nombre + '</b>' +  ' comentó el ' + fecha.getUTCDate() + '/' + fecha.getMonth() + '/' + fecha.getUTCFullYear() + ' a las ' + fecha.getHours() + ':' + fecha.getMinutes() + '</p>' +
    '<p class="comen">' + mensaje + '</p>';
    
    comentario.insertAdjacentHTML('beforeend', nuevo);
    reset();
}

function reset(){
    document.getElementById("nombre").value = "";
    document.getElementById("mail").value = "";
    document.getElementById("msg").value = "";
}

String.prototype.replaceAt = function(index, replacement) {
    return this.substr(0, index) + replacement + this.substr(index + replacement.length);
}

function convierteAsterisco(palabra, pos_inicio){
    var nuevoTexto = document.getElementById("msg").value;

    for(var i = 0; i < palabra.length; i++){
        nuevoTexto = nuevoTexto.replaceAt(pos_inicio, "*");
        pos_inicio = pos_inicio + 1;
    }

    document.getElementById("msg").value = nuevoTexto;
}

function checkMalasPalabras(){
    var mal = ["puto", "tonto", "maricon", "feo", "guarra", "gilipollas", "subnormal", "pito", "pene", "coño"];
    var y = document.getElementById("msg").value;
    var pos_inicio = -1;
    var nueva = "";
       
    mal.forEach(function(element){
        pos_inicio = y.search(element.toString());

        if(pos_inicio != -1){
            var palabra = "";

            var pos_final = pos_inicio;
            while(y[pos_final] != " " && pos_final != y.length){
                palabra = palabra + y[pos_final];
                pos_final = pos_final + 1;
            }

            convierteAsterisco(palabra, pos_inicio);
        }
    });
}
