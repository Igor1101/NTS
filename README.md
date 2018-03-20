# NTS (Network Traffic Service) 
A daemon which sniffs packets, saves ip addresses, number of incoming packets from each ip, last time of transmitted data to 
```
/var/log/NTS.log
```
in format %x:%llx:%lx:%s (or hex int converted ip address, long long int (64bit) amount of packets), time_t time, %s interface

### Building & Installing
Before upgrading this daemon to a new version, please remove old log file.
should have LINUX like OS, (it can`t be compiled under BSDs without change because of difference in socket libraries)
cmake automative tool with version >= 3.7(or change version in CMakeLists.txt)
You should also change name of default sniffing interface in CMakeLists.txt(1 line), example:
    ```
        set(DEFAULT_IF "enp19s0")
    ```
    and remove old log file 
        
    ```
      sudo rm /var/log/NTS.log
      cmake ./ 
      make
    ```
as a result you have object file "NTS"


### Running the tests
How to work with it?
   ``` 
    #Prints useful information and exits:
    sudo ./NTS --help
    #starts console:
    sudo ./NTS --console
    #starts console and outputs debug information, be more verbose
    sudo ./NTS --debug
    #just start
    sudo ./NTS
   ```
   in debug mode NTS reopens its stdout to /dev/console, every ip received will be printed in real time.
### Console
### if any command is not understood:
```
[CMD] --help
```
#### prints status info for [iface] or for all interfaces.
```
-> stat [optional iface]
```
#### prints number of received packets for appropriate address(for ex 255.255.255.255)
```
-> show 255.255.255.255
```
#### select iface to sniff(can be used at any time)
```
-> select [iface]
```
#### start sniffing
```
-> start
```
#### stop 
```
-> stop
```
#### exit from console (dont stop NTS)
```
-> exit
-> quit
```
### NEW!!! output command [stat] in  less format and exit:
```
-> less

```
### Saving info into file (/var/log/NTS.log)
Daemon updates information in logfile after it receives SIGHUP or SIGTERM and when you type in console command stat[iface].
