from calculator import Calculator
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol


def main():
    # Make socket
    transport = TSocket.TSocket('localhost', 9090)

    # Buffering is critical. Raw sockets are very slow
    transport = TTransport.TBufferedTransport(transport)

    # Wrap in a protocol
    protocol = TBinaryProtocol.TBinaryProtocol(transport)

    # Create a client to use the protocol encoder
    client = Calculator.Client(protocol)

    # Connect!
    transport.open()

    print('Confirmación de la conexión por el método ping()')
    client.ping()
    print('ping()\n')

    print('Operaciones básicas con double')
    sum_ = client.add(1.5, 1.5)
    print('1.5+1.5 = %d' % sum_)

    res_ = client.Subtract(4.2, 4.1)
    print('4.2-4.1 = %d' % res_)

    mul_ = client.Multiply(2.5, 2.5)
    print('2.5*2.5 = %d' % mul_)

    div_ = client.Divide(5, 2)
    print('5/2 = %d' % div_)

    print('Operaciones básicas con vectores enteros')
    v1 = [4, 4, 4]
    v2 = [2, 2, 2]
    print('Primer vector v1:', v1)
    print('Segundo vector v2:', v2)

    v3 = client.listAdd(v1, v2)
    print('v1 + v2:', v3)

    v3 = client.listSubtract(v1, v2)
    print('v1 - v2:', v3)

    v3 = client.listMultiply(v1, v2)
    print('v1 * v2:', v3)

    v3 = client.listDivide(v1, v2)
    print('v1 / v2:', v3)

    # Close!
    transport.close()


if __name__ == '__main__':
    try:
        main()
    except Thrift.TException as tx:
        print('%s' % tx.message)