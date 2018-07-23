^+l::

InputBox, secret, Enter Secret, , 640, 480
if secret =
    Exit
Send, kubectl create secret generic my-secrets --from-literal=hub0-cs='%secret%' && kubectl create serviceaccount --namespace kube-system tiller && kubectl create clusterrolebinding tiller-cluster-rule --clusterrole=cluster-admin --serviceaccount=kube-system:tiller && kubectl patch deploy --namespace kube-system tiller-deploy -p '{{}"spec":{{}"template":{{}"spec":{{}"serviceAccount":"tiller"{}}{}}{}}{}}' && helm init --service-account tiller -upgrade && helm repo update && cd iot-edge-virtual-kubelet-provider/src/charts/iot-edge-connector/ && helm install -n hub0 --set rbac.install=true . {Enter}

return 