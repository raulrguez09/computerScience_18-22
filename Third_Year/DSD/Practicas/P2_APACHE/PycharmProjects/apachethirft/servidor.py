from calculator import Calculator
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer


class CalculatorHandler:
    def __init__(self):
        self.log = {}

    def ping(self):
        print('ping()')

    def add(self, n1, n2):
        print('add(', n1, ',', n2, ')')
        return n1 + n2

    def Subtract(self, n1, n2):
        print('subtract(', n1, ',', n2, ')')
        return n1 - n2

    def Multiply(self, n1, n2):
        print('multiply(', n1, ',', n2, ')')
        return n1 * n2

    def Divide(self, n1, n2):
        print('divide(', n1, ',', n2, ')')
        return n1 / n2

    def listAdd(self, v1, v2):
        return [x + y for x, y in zip(v1, v2)]

    def listSubtract(self, v1, v2):
        return [x - y for x, y in zip(v1, v2)]

    def listMultiply(self, v1, v2):
        return [x * y for x, y in zip(v1, v2)]

    def listDivide(self, v1, v2):
        return [x // y for x, y in zip(v1, v2)]


if __name__ == '__main__':
    handler = CalculatorHandler()
    processor = Calculator.Processor(handler)
    transport = TSocket.TServerSocket(host='127.0.0.1', port=9090)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()

    server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)

    print('Starting the server...')
    server.serve()
    print('done.')
