# Virtual Kubelet on IoT Hub 
  - For a full guide, Open the Kubernetes_AIoT_VK Document.
  - Follow along with this video: https://www.youtube.com/watch?v=XbkLWmjww8I

# AutoHotKey
To use the hotkeys to automate this process, first install AutoHotKey

  - The command for the first half is Ctrl+Shift+J
  - The command for the latter half is Ctrl+Shift+L

#

If you are looking to do this manually, you may just follow the steps provided by the "Guides" above

#

https://github.com/azure/iot-edge-virtual-kubelet-provider


# Kubernetes, Azure IoT Hub/Edge, and Virtual Kubelet

### Definitions:
  - [Kubernetes](https://kubernetes.io/): Kubernetes (koo-ber-neh-tees) is an open-source system for automating deployments, scaling, and management of containerized applications.” 
    [Here](https://www.youtube.com/watch?v=IMOZCDhH7do) is a simplified video, explaining what Kubernetes does. You should view Kubernetes as a service for container management.
  - [IoT Hub](https://docs.microsoft.com/en-us/azure/iot-hub/about-iot-hub):  IoT Hub is a Microsoft Azure service that enables you to receive telemetry data (data collected at remote points and transmitted to receiving equipment for monitoring) at scale from your IoT devices and monitor/ manage said devices.
  - [Azure IoT Edge](https://azure.microsoft.com/en-us/services/iot-edge/):  “Azure IoT Edge is a service that builds on top of IoT Hub. This service is meant for customers who want to analyze data on devices, a.k.a. "at the edge", instead of in the cloud. By moving parts of your workload to the edge, your devices can spend less time sending messages to the cloud and react more quickly to changes in status” 
Basically, we will be using IoT Edge to kill cloud computing. We will be pushing containers onto edge devices, rather than doing work in the cloud. By having the devices do the computing, or storing the data and sending it to the cloud in chunks, the processes being done are sped up and do not require a constant connection to a server. 

  - [Virtual Kubelet](https://github.com/virtual-kubelet/virtual-kubelet): “Virtual Kubelet is an open source Kubernetes kubelet implementation that masquerades as a kubelet for the purposes of connecting Kubernetes to other APIs. This allows the nodes to be backed by other services like… IoT Edge. The primary scenario for VK is enabling the extension of the Kubernetes API into serverless container platforms like ACI, Fargate, and Hyper.sh, though we are open to others.”
We will be using Virtual Kubelet, in some sense, as the bridge between Azure IoT Hub and Kubernetes. 

### Why Virtual Kubelet?

Virtual Kubelet will allow us to more easily manage and scale IoT Edge Deployments from inside a Kubernetes environment. <br/>

I highly suggest you read [this short article](https://thenewstack.io/kubernetes-for-edge-computing-the-microsoft-azure-approach/) on the topic. This gives a brief explanation of everything I have spoken about thus far, and succinctly explains the advantages of using this technology. <i/>(For an even less reading, you can ctrl+f “Virtual Kubelet” and start reading from the first paragraph to mention it)
