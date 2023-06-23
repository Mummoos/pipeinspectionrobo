#include <pgmspace.h>

#define SECRET
#define THINGNAME "Esp_Cam_Pipe"


const char WIFI_SSID[] = "VERDANT PW 4G";
const char WIFI_PASSWORD[] = "Verdant@123456";
const char AWS_IOT_ENDPOINT[] = "a3b4ttqshsk2ua-ats.iot.eu-north-1.amazonaws.com";

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWjCCAkKgAwIBAgIVAPzH5EmSBK23l6iz50EhOUrTjG7IMA0GCSqGSIb3DQEB
CwUAME0xSzBJBgNVBAsMQkFtYXpvbiBXZWIgU2VydmljZXMgTz1BbWF6b24uY29t
IEluYy4gTD1TZWF0dGxlIFNUPVdhc2hpbmd0b24gQz1VUzAeFw0yMzA1MTQxNTM5
NTlaFw00OTEyMzEyMzU5NTlaMB4xHDAaBgNVBAMME0FXUyBJb1QgQ2VydGlmaWNh
dGUwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDapGRMvKhaVVFJaru6
AS9/m3l5PZurDdLiogHkwzQHfldtVXmYVyPAy4otMWZLMjjq3iFlzGXqXrv8Hn3j
LFno4Jse20RblJ5S6kSSxz/jmFXlhVLcu/rwS2Zt7NZEKKpRljx+f7ugKtXVia/P
GRZBSujh5zXCTbVmx7AHY5ZibiJjovM5XG2/xC3G1CLW4AN25d/ltIGqmCTLEwXq
1lJIpn1mzA9ANMPDltXNAGr1xr89BB5GpSoDb0SvkQjgEZh3/cMJb7NX/6u3QaVF
VQHe+zGEtLde16MZqPrAElDUY7p+Tu+bbkXtHx+sLcxodttAVdXqzrvu8Jv6WqhW
XYRXAgMBAAGjYDBeMB8GA1UdIwQYMBaAFMLvvnPSPb+UmZd3gDLKOFwVddUmMB0G
A1UdDgQWBBQ93R+WbBTAlFUjIdEQGXblTmZ3CDAMBgNVHRMBAf8EAjAAMA4GA1Ud
DwEB/wQEAwIHgDANBgkqhkiG9w0BAQsFAAOCAQEANxFQ5lsFRKRKsX1CyYfFiSf/
9daA7+XbfVzza4kk5ijWErZdlkhOaihmT4qPt6uZaDDnFsAJLbDUbE6/ATZuhJmd
300RPSqRwnIB7rpp/p0GnLOzDtE3EJ5W9w7L3slf04S20WHRr/FbIhUBAjWkGsSd
y6T9Ws6rMUUqQkz60CzZI9+MZb1diJQFRMzkss1I53RrbmxNHNhEkufd5BX+5fxw
Ls1LJhoGgY6yflrJgSaLa99lmR7rtRlfSOpwA8Pm7hOsEV8AqAVagqPyfOV41qBK
x0PI1NQgFNTCHUQ4O+8CUb4D+13xhzI7BX0UKpovvfW/OW9c46ihoCuSbE3oHA==
-----END CERTIFICATE-----

)KEY";

// Device Private Key
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEA2qRkTLyoWlVRSWq7ugEvf5t5eT2bqw3S4qIB5MM0B35XbVV5
mFcjwMuKLTFmSzI46t4hZcxl6l67/B594yxZ6OCbHttEW5SeUupEksc/45hV5YVS
3Lv68EtmbezWRCiqUZY8fn+7oCrV1YmvzxkWQUro4ec1wk21ZsewB2OWYm4iY6Lz
OVxtv8QtxtQi1uADduXf5bSBqpgkyxMF6tZSSKZ9ZswPQDTDw5bVzQBq9ca/PQQe
RqUqA29Er5EI4BGYd/3DCW+zV/+rt0GlRVUB3vsxhLS3XtejGaj6wBJQ1GO6fk7v
m25F7R8frC3MaHbbQFXV6s677vCb+lqoVl2EVwIDAQABAoIBACuM3yWh1m7X268i
AW6VWd6zG0kZCm7R/BWEa5gjgbOUaNmwUt4TTV3TrRw/YL7NrCSsRj6+rfY3FH6t
nCmp5ebLBlrpFf6f5cFiRHJwGbu91i43lj+9echvXGG88Rj2eKZzpG0WCEto/Nrh
6BD6UEKFJ0oIAd9IFz/3uopePdAw/YKBedPKeDo5afNlOCyYxpaIPk651FYhMZP2
t2zILBxSu9E515g2Lvs7HavfMTjMVgw9Dmz8SVwBspAtZV2fVOWy0UB8epA0kMKn
ZHdb7L9EzugRqFQQ8aiuu+BTScieHCxYw9t6HmemmTV+SiFYBLvfkCQ2jJ8t/PfI
1+wL0SECgYEA84oRDzw7Y4AtvGLOy5Xm/pr7R9QEWQikmDsMXIhISc5ys69Us4OZ
OHMEr2Cv28FXNkFk4ke8tk2xXChZXx6uPY7szwJ4v1i2Y4F+VSZGt6IpMmlWcYZp
jWYdIbZ/2GKKQrkCtXHuCXOhUpG9mjVuAzG8r32dQKLMTyxh4gdNDMkCgYEA5dQ3
ZkwxtXoI94NWBz7B97u9AH9ZazFQ3PvNLLWEP9lCViGRTpivU+fs7jz/ExF/cUgf
M6QEcxOeKrKY8R5ykB0yjC6LbQWeN6JxeXxHMtaJ8VyzVj7aJVuullb5EoJnMxWl
BWd4v0iP8af1wNsYuiwWTmXYZI3diotCZkbVOB8CgYBN7AojTslNv9Bia1bxSsg7
BImL5OlzN1G6p4IABVbjzptipKG8Qkn/BsYj+xKphIYMBQZrZDqcNeWesAZQafek
GJvqbEcIKjFJS0CJrBKKZOc7ivquniwdouOFSuhC6tyEFsAoIAjim02tppX8xkWp
3fsaR13ONYibeH7lHCLqCQKBgGeE2dsy8KTsLcPGnWYwB1AdeLkTo2Qb129h332G
2OWlZzLCdd+v+DDT4y0/viiJlhyhPqSU+QgYSwKyZR8d9r4g2Ja5lEVr5WLrwS7W
In+skH9toL11G+79x7qhvBhxMiiZVDYF8CZAec2AOLpANXgNyZJQX1KTb7kqlqLY
vstDAoGBAIeI08DYGsby5cUgMq4bPijfkEuu8P5Q6zPM9DQ7qskgnXGc3R6bfUND
PqGFaCyPJAErYRLqY6hadKYsOzBTYJ9NksE3pvDs2PpN7L0RP/vKTUopkeXaUjzO
aaJZSQsY4Svd62BxcoYyBwedfLRcb1JzlqG56UjStwxL4xO53Ira
-----END RSA PRIVATE KEY-----

)KEY";
