ab -n 100 -c 100 http://localhost:80/api/v1/users?login=defuser&password=123&type=0
[1] 4673
[2] 4674
lapayka@lapayka-VirtualBox:~/study/3cbdcw/proj/DBCW/64/bin$ This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /api/v1/users?login=defuser
Document Length:        0 bytes

Concurrency Level:      100
Time taken for tests:   0.025 seconds
Complete requests:      100
Failed requests:        0
Non-2xx responses:      100
Total transferred:      38400 bytes
HTML transferred:       0 bytes
Requests per second:    4035.51 [#/sec] (mean)
Time per request:       24.780 [ms] (mean)
Time per request:       0.248 [ms] (mean, across all concurrent requests)
Transfer rate:          1513.32 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    5   1.5      5       7
Processing:     2   11   3.0     10      15
Waiting:        1   11   2.9     10      14
Total:          8   16   2.2     16      20

Percentage of the requests served within a certain time (ms)
  50%     16
  66%     17
  75%     17
  80%     18
  90%     19
  95%     19
  98%     20
  99%     20
 100%     20 (longest request)
ab -n 100 -c 100 http://localhost:80/api/v1/users?login=defuser&password=123&type=0^C
[1]-  Завершён        ab -n 100 -c 100 http://localhost:80/api/v1/users?login=defuser
[2]+  Завершён        password=123
lapayka@lapayka-VirtualBox:~/study/3cbdcw/proj/DBCW/64/bin$ ab -n 100 -c 100 http://localhost:8000/api/v1/users?login=defuser&password=123&type=0
[1] 4682
[2] 4683
lapayka@lapayka-VirtualBox:~/study/3cbdcw/proj/DBCW/64/bin$ This is ApacheBench, Version 2.3 <$Revision: 1843412 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        oatpp/1.3.0
Server Hostname:        localhost
Server Port:            8000

Document Path:          /api/v1/users?login=defuser
Document Length:        0 bytes

Concurrency Level:      100
Time taken for tests:   0.021 seconds
Complete requests:      100
Failed requests:        0
Non-2xx responses:      100
Total transferred:      33700 bytes
HTML transferred:       0 bytes
Requests per second:    4687.35 [#/sec] (mean)
Time per request:       21.334 [ms] (mean)
Time per request:       0.213 [ms] (mean, across all concurrent requests)
Transfer rate:          1542.62 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    7   2.4      7      11
Processing:     1    5   2.0      5      12
Waiting:        1    4   1.9      5       8
Total:          5   12   2.9     12      19

Percentage of the requests served within a certain time (ms)
  50%     12
  66%     14
  75%     14
  80%     15
  90%     16
  95%     17
  98%     18
  99%     19
 100%     19 (longest request)


