# Basic Steps

This is a copy of the Basic Steps, but not in notepad<br/>
I suggest you follow along with my [YouTube Video](https://www.youtube.com/watch?v=XbkLWmjww8I) and work in the [Azure Portal](https://portal.azure.com/), so you don't have to install anything. You can create a free account [Here](https://azure.microsoft.com/en-us/free/)

## Clone the Virtual Kubelet Provider GitHub into Storage
```sh
git clone https://github.com/Azure/iot-edge-virtual-kubelet-provider.git
```

## Create a Resource Group, and IoT Hub, and an AKS Cluster

- I prefer creating the IoT Hub through the Azure Interface, and this is what you will see my do in the video. If you prefer this:
```sh
az group create -n <resource group> -l <location: westus, eastus>
az aks create -n <aks cluster name> -g <resource group> -c <node count, 1> --generate-ssh-keys
```
Follow this with navigating to the IoT Hub section, clicking + in the top left corner, and creating a new hub with the resource group you just created. The free options will be fine for this demo.

- If you prefer creating the Hub through bash, use this instead:
```sh
az group create -n <resource group> -l <location: westus, eastus>
az iot hub create -n <iot hub name> -g <resource group> --sku <s1>
az aks create -n <aks cluster name> -g <resource group> -c <node count, 1> --generate-ssh-keys
```
*you may want to add* ```sh --no-wait ``` *to the end of the previous command* (```az aks create```), *so you can interact with the command line while the aks cluster is being created*

## Connect to the AKS Cluster
```sh
az aks get-credentials -n <aks cluster new> -g <resource group>
```

## Generate Secrets 

You can find the iot-hub-owner-connection string by first navigating to the IoT Hub you created. From there, in the bar on the left, scroll down to the 'Shared Access Policies' under the settings tab. Now click on the iothubowner bar, which should pop up a window on the right. Near the bottom you will see the primary connection string (the third one down). You can copy it by clicking the blue button to the right of the string.
```sh
kubectl create secret generic my-secrets --from-literal=hub0-cs='<iot-hub-owner-connection-string>'
```

## Download the Virtual Kubelet Provider through Helm
```sh
kubectl --namespace kube-system create serviceaccount tiller
kubectl create clusterrolebinding tiller-cluster-rule --clusterrole=cluster-admin --serviceaccount=kube-system:tiller
helm init --service-account tiller
```
<br/> *wait a second so the tiller has time to initiate* <br/>
```sh
cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/
helm install -n hub0 --set rbac.install=true .
```

## Check the results
```sh
kubectl get nodes
kubectl get pods
```

## Test a Sample Deployment
```sh
cd
kubectl apply -f \
iot-edge-virtual-kubelet-provider/src/Microsoft.Azure.VirtualKubelet.Edge.Provider/sample-deployment.yaml
```

## Scaling

- Scaling Pods, through Kubernetes (very fast)
```sh
kubectl scale deployments/<deployment, kubectl get deployments> --replicas <number of replicas>
```
- Scaling Nodes, through Azure (very slow)
```sh
az aks scale -n <aks cluster name> -g <resource group> -c <node count> 
```

## Update
```sh
az aks upgrade -k <version to upgrade to> -n <aks cluster name> -g <resource group>
```

## Clean up
- Group delete (Everything)
```sh
az group delete -n <resource group> --no-wait -y
```
- Cluster delete
```sh
az aks delete -n <aks cluster> -g <resource group> --no-wait -y
```
