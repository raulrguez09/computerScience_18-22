# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require './JugadorBaloncesto'
require './Pista'
require './JugadorBaloncesto'
require './PistaBaloncesto'

module Prototipo
  class FactoriaBaloncesto
    
    def crearPistaPartido(id)
      return PistaBaloncesto.new(id)
    end
    
    def crearJugador(id)
      return JugadorBaloncesto.new(id)
    end
  end
  
end
