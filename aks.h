^+j::

InputBox, resource, Enter Resource, , 640, 480
if resource = 
    Exit
InputBox, hub, Enter Hub, , 640, 480
if hub =
    Exit
InputBox, aks, Enter AKS, , 640, 480
if aks = 
    Exit
InputBox, nodes, Enter Nodes, , 640, 480
if nodes = 
    Exit

Send, az group create -n %resource% --location eastus && az iot hub create -n %hub% -g %resource% --sku S1 && az aks create -g %resource% -n %aks% -c %nodes% --generate-ssh-keys && az aks get-credentials -g %resource% -n %aks% && kubectl get nodes {Enter}

InputBox, secret, Enter Secret, , 640, 480
if secret =
    Exit
Send, kubectl create secret generic my-secrets --from-literal=hub0-cs=’l’ && helm init && kubectl create serviceaccount --namespace kube-system tiller && kubectl create clusterrolebinding tiller-cluster-rule --clusterrole=cluster-admin --serviceaccount=kube-system:tiller && kubectl patch deploy --namespace kube-system tiller-deploy -p ‘{“spec”:{“template”:{“spec”:{“serviceAccount”:”tiller”}}}}’ && helm init --service-account tiller --upgrade && helm repo update && cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/ && helm install -n hub0 --set rbac.install=true . 
return 