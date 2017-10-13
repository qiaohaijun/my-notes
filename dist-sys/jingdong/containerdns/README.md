### Introduction
ContainerDNS is used as internal DNS server for k8s cluster, 
and use DNS library : https://github.com/miekg/dns. 
containerdns-kubeapi will monitor the services in k8s cluster,when the service is created and has been assigned with external ips, the user(docker)in cluster can access the service with the domain. 
When the domain has multiple ips, the containerdns will choose one actived for the user randomly, it seems like a load balancer. 
Also the containerdns offer "session persistence", that means we query one domain from one user ip, then the user access the domain later, the user will get the same service ip.

