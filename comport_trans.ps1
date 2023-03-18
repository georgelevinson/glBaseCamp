    $port= new-Object System.IO.Ports.SerialPort COM9,115200,None,8,one
    $port.Open()
    $port.WriteLine($args[0])
    $port.ReadLine()
    $port.Close()