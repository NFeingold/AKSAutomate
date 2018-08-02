# Basic Steps

This is a copy of the Basic Steps, but not in notepad

```sh
git clone https://github.com/Azure/iot-edge-virtual-kubelet-provider.git
```
```sh
az group create -n <resource group> -l <location: westus, eastus>
az iot hub create -n <iot hub name> -g <resource group> --sku <s1>
az aks create -n <aks cluster name> -g <resource group> -c <node count, 1> --generate-ssh-keys
	(optional): -s <version: Standard_A2_v2> --no-wait
az aks get-credentials -n <aks cluster new> -g <resource group>
```
```sh
kubectl create secret generic my-secrets --from-literal=hub0-cs='<iot-hub-owner-connection-string>'
```
```sh
kubectl --namespace kube-system create serviceaccount tiller
kubectl create clusterrolebinding tiller-cluster-rule --clusterrole=cluster-admin --serviceaccount=kube-system:tiller
helm init --service-account tiller
cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/
```
```sh
helm install -n hub0 --set rbac.install=true .
```
```sh
kubectl get nodes
kubectl get pods
```

# Sample Deployment
```sh
cd
kubectl apply -f \
iot-edge-virtual-kubelet-provider/src/Microsoft.Azure.VirtualKubelet.Edge.Provider/sample-deployment.yaml
```

# Scaling
- Scaling Nodes, through Azure (very slow)
```sh
az aks scale -n <aks cluster name> -g <resource group> -c <node count> 
```
- Scaling Pods, through Kubernetes (very fast)
```sh
kubectl scale deployments/<deployment, kubectl get deployments> --replicas <number of replicas>
```
# Update
```sh
az aks upgrade -k <version to upgrade to> -n <aks cluster name> -g <resource group>
```

# Delete 
- Group delete (Everything)
```sh
az group delete -n <resource group> --no-wait -y
```
- Cluster delete
```sh
az aks delete -n <aks cluster> -g <resource group> --no-wait -y
```
