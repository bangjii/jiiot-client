wifi.setmode(wifi.STATION);                 --set client
wifi.sta.config("redmi" ,"12345678"); 		--user pass
wifi.sta.autoconnect(1)                     --wifi auto connect
--uncomment if you have to set static ip address
--wifi.sta.setip({ip="192.168.43.119",netmask="255.255.255.0",gateway="192.168.43.1"})
uart.setup(0,9600,8,0,1)                    --serial config 
print(wifi.sta.getip())                     --show ipconfig

--main function
function post(sensor, nilai)
    host = "iotcampus.net"
    apikey = "yourAPIkey"
	if (sensor == "Distance" or sensor == "Motion") then
		if (nilai ~= nil) then
			valsen = nilai
		elseif (nilai == nil) then
			valsen = 0
		end
		postData = "/jiiot/api/kirim.php?key="..apikey.."&sensor="..sensor.."&nilai="..valsen
		connout = net.createConnection(net.TCP, 0) 
		--fungsi ketika konek
		connout:on("connection", function(connout, payloadout)  
			connout:send("GET "..postData
			.. " HTTP/1.1\r\n"
			.. "Host: "..host.."\r\n"
			.. "Connection: close\r\n"
			.. "Accept: */*\r\n"
			.. "User-Agent: Mozilla/4.0 (compatible; esp8266 Lua; Windows NT 5.1)\r\n"
			.. "\r\n")
		end)
		--fungsi ketika putus koneksi
		connout:on("disconnection", function(connout, payloadout)
			connout:close();
			collectgarbage();
		end)
		--fungsi koneksi  
		connout:connect(80,host)
	end
end
