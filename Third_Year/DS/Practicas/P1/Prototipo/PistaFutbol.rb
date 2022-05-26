# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
require './Pista'
module Prototipo

class PistaFutbol < Pista
  public
  def initialize(id)
    super(id)
    @players = Array.new
    @tipo = "Futbol"
  end

  def clonar
    return PistaFutbol.new(@id)
  end

  def addJugadores(jug)
    @players << jug
  end

  attr_accessor :players
end

end