# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Prototipo

require './FactoriaFutbol'
require './FactoriaBaloncesto'
require './JugadorFutbol'
require './JugadorBaloncesto'
require './FactoriaFutbol'
require './Pista'
require './PistaFutbol'
require './PistaBaloncesto'

class Cliente

    @@pistas = Array.new
    @jugador = nil
    
    def self.generar_numero_participantes
      @jugadores = 7 + rand(10)
    end

    def self.main
      generar_numero_participantes()
      
      # Creamos la factoría, el jugador que vamos a clonar y la carrera
      @factoria = FactoriaFutbol.new
      @jugador = @factoria.crearJugador(0)
      @@pistas << @factoria.crearPistaPartido(0)

      @@pistas[0].setJugadores(@jugadores)
      
      for i in 0..@jugadores do
        # Clonamos la jugador, la añadimos al array de jugadors de la carrera y actualizamos el dorsal
        jugador = @jugador.clonar
        @@pistas[0].addJugadores(jugador)
        @@pistas[0].players[i].dorsal = i + rand(80)
      end
      
      # Creamos la factoría, la jugador que vamos a clonar y la carrera
      @factoria = FactoriaBaloncesto.new
      @jugador = @factoria.crearJugador(100)
      @@pistas << @factoria.crearPistaPartido(1)
      
      @@pistas[1].setJugadores(@jugadores)

      for j in 0..@jugadores do
        # Clonamos la jugador, la añadimos al array de jugadors de la carrera y actualizamos el dorsal
        jugador = @jugador.clonar
        @@pistas[1].addJugadores(jugador)
        @@pistas[1].players[j].dorsal = j + rand(80)
      end
      
      for i in 0..@jugadores do
        @@pistas[0].players[i].jugar
        @@pistas[1].players[i].jugar
      end

      sleep(rand(3))

      for i in 0..@jugadores do
        if(3 == rand(5))
          @@pistas[0].players[i].lesion
        end
        if(3 == rand(5))
          @@pistas[1].players[i].lesion
        end
      end
    
      sleep(5)

      for i in 0..@jugadores do
        @@pistas[0].players[i].terminarJugar
        @@pistas[1].players[i].terminarJugar
      end
    end
  
    Cliente.main
end

end