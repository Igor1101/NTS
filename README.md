# NTS (Network Traffic Service)
A daemon which sniffs packets, saves ip addresses and number of incoming packets from each ip to 
```
/var/log/NTS.log
```
in format %x:%llx (or hex int converted ip address, long long int (64bit) amount of packets).

### Building & Installing
should have UNIX like OS, 
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
Now program has no TUI.
if you`d like to see the process of receiving/saving IPs(whatever),
   run NTS in debug mode
   ``` 
   sudo ./NTS -debug
   ```
   in debug mode NTS reopens its stdout to /dev/tty8, every ip received will be printed in real time.
if you`d like to see all already saved information in human readable mode, hit keys ^C (CONTROL-C) or send SIGINT when running in debug mode in /dev/tty8.
### Saving info into file (/var/log/NTS.log)
Daemon updates information in logfile after it receives SIGHUP or SIGTERM.
