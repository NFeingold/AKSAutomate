# Basic Steps

This is a copy of the Basic Steps, but not in notepad

### Clone This GitHub into storage
```sh
git clone https://github.com/Azure/iot-edge-virtual-kubelet-provider.git
```

### Create a Resource Group, and IoT Hub, and an AKS Cluster
```sh
az group create -n <resource group> -l <location: westus, eastus>
az iot hub create -n <iot hub name> -g <resource group> --sku <s1>
az aks create -n <aks cluster name> -g <resource group> -c <node count, 1> --generate-ssh-keys
```
*you may want to add* ```sh --no-wait ``` *to the end of the previous command, so you can interact with the command line while the aks cluster is being created*
```sh
az aks get-credentials -n <aks cluster new> -g <resource group>
```

### Generate Secrets 
```sh
kubectl create secret generic my-secrets --from-literal=hub0-cs='<iot-hub-owner-connection-string>'
```

### Download the Virtual Kubelet Provider through Helm
```sh
kubectl --namespace kube-system create serviceaccount tiller
kubectl create clusterrolebinding tiller-cluster-rule --clusterrole=cluster-admin --serviceaccount=kube-system:tiller
helm init --service-account tiller
cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/
```
<br/> *wait a second so the tiller has time to initiate* <br/>
```sh
helm install -n hub0 --set rbac.install=true .
```

### Check the results
```sh
kubectl get nodes
kubectl get pods
```

### Test a Sample Deployment
```sh
cd
kubectl apply -f \
iot-edge-virtual-kubelet-provider/src/Microsoft.Azure.VirtualKubelet.Edge.Provider/sample-deployment.yaml
```

### Scaling

- Scaling Pods, through Kubernetes (very fast)
```sh
kubectl scale deployments/<deployment, kubectl get deployments> --replicas <number of replicas>
```
- Scaling Nodes, through Azure (very slow)
```sh
az aks scale -n <aks cluster name> -g <resource group> -c <node count> 
```

### Update
```sh
az aks upgrade -k <version to upgrade to> -n <aks cluster name> -g <resource group>
```

### Clean up
- Group delete (Everything)
```sh
az group delete -n <resource group> --no-wait -y
```
- Cluster delete
```sh
az aks delete -n <aks cluster> -g <resource group> --no-wait -y
```
