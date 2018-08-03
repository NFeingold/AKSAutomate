# Steps to Use
Download the above two .exe files. 

Run both of the files by double clicking on them <br/>

Pressing Ctrl+Shift+J will prompt you for:
  - Resource Name 
  - Hub Name
  - AKS Cluster Name
  - Number of Nodes

This will paste the following:
```sh
az group create -n myResource --location eastus && az iot hub create -n myHub -g myResource --sku S1 && az aks create -g myResource -n myAKS -c 1 --generate-ssh-keys && az aks get-credentials -g myResource -n myAKS && kubectl get nodes 
```
Pressing Ctrl+Shit+L will prompt you for:
  - Secret Key
  
This will paste the following:
```sh
kubectl create secret generic my-secrets --from-literal=hub0-cs=’My Secret’ && kubectl --namespace kube-system create serviceaccount tiller && kubectl create clusterrolebinding tiller-cluster-rerrole=cluster-admin --serviceaccount=kube-system:tiller && helm init --service-account tiller && cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/ && helm install -n hub0 --set rbac.install=true . && cd 
```
**Please remember to click in the terminal or notepad before using these commands**
