# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require './Jugador'

module Prototipo

class Pista

  @@jugadores = 0
  @tipo = nil

  attr_accessor :players

  def setJugadores(jugs)
    @@jugadores = jugs
  end
  
  def self.getJugadores
    return @@jugadores
  end
    
  private
  def initialize(id)
    @id = id
    @players = Array.new
  end

  def clonar
    return Pista.new(@id)
  end

  def addJugador(jug)
    @players << jug
  end

end

end