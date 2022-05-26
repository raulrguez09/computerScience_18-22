# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

require './JugadorFutbol'
require './PistaFutbol'

module Prototipo
  class FactoriaFutbol

    def initialize
    end
    
    def crearPistaPartido(id)
      return PistaFutbol.new(id)
    end
    
    def crearJugador(id)
      return JugadorFutbol.new(id)
    end
  end
  
end