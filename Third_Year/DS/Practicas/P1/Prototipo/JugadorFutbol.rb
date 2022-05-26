# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.
module Prototipo

require './Jugador'

class JugadorFutbol < Jugador

  public
  def initialize(dorsal)
    super(dorsal)
    @tipo = "Futbol"
    @lesion = false
  end

  def clonar
    return JugadorFutbol.new(@dorsal)
  end

  def jugar 
    puts "Jugador con dorsal #{@dorsal} empieza a jugar al #{@tipo}"
  end

  def terminarJugar
    if (!@lesion)
      puts "Jugador con dorsal #{@dorsal} termina de jugar al #{@tipo}"
    end
  end

  def lesion
    puts "Jugador con dorsal #{@dorsal} se va lesionado del partido de #{@tipo}"
    @lesion = true
  end

  attr_accessor :dorsal
end

end
