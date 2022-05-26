# To change this license header, choose License Headers in Project Properties.
# To change this template file, choose Tools | Templates
# and open the template in the editor.

class Jugador

    @dorsal = nil
    @tipo = nil

    attr_accessor :dorsal , :tipo

    private
    def initialize(dorsal)
      @dorsal = dorsal
    end

    def clonar
      return Bicicleta.new(@dorsal)
    end

end
