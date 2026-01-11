helm repo add nvidia https://helm.ngc.nvidia.com/nvidia \
   && helm repo update

helm install nim-operator nvidia/k8s-nim-operator --create-namespace -n nim-operator

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

$ docker login nvcr.io
Username: $oauthtoken
Password: <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>

export NGC_API_KEY=<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>
export LOCAL_NIM_CACHE=~/.cache/nim
mkdir -p "$LOCAL_NIM_CACHE"
docker run -it --rm \
    --gpus all \
    --shm-size=16GB \
    -e NGC_API_KEY \
    -v "$LOCAL_NIM_CACHE:/opt/nim/.cache" \
    -u $(id -u) \
    -p 8000:8000 \
    nvcr.io/nim/meta/llama-3.1-70b-instruct:latest

curl -X 'POST' \
'http://0.0.0.0:8000/v1/chat/completions' \
-H 'accept: application/json' \
-H 'Content-Type: application/json' \
-d '{
    "model": "meta/llama-3.1-70b-instruct",
    "messages": [{"role":"user", "content":"Write a limerick about the wonders of GPU computing."}],
    "max_tokens": 64
}'

kubectl create ns nim-service

kubectl create secret -n nim-service docker-registry ngc-secret \
    --docker-server=nvcr.io \
    --docker-username='$oauthtoken' \
    --docker-password=<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>

kubectl create secret -n nim-service generic ngc-api-secret \
    --from-literal=NGC_API_KEY=<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>


kubectl run --rm -it -n default curl --image=curlimages/curl:latest -- ash

curl -X "POST" \
 'http://llama-31-70b-instruct.nim-service:8000/v1/chat/completions' \
  -H 'Accept: application/json' \
  -H 'Content-Type: application/json' \
  -d '{
        "model": "meta/llama-3.1-70b-instruct",
        "messages": [
        {
          "content":"What should I do for a 4 day vacation at Cape Hatteras National Seashore?",
          "role": "user"
        }],
        "top_p": 1,
        "n": 1,
        "max_tokens": 1024,
        "stream": false,
        "frequency_penalty": 0.0,
        "stop": ["STOP"]
      }'


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



helm fetch https://helm.ngc.nvidia.com/nim/charts/nim-llm-1.3.0.tgz --username='$oauthtoken' --password=$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

import getpass
import os

if not os.environ.get("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"):
  os.environ["NVIDIA_API_KEY"] = getpass.getpass("Enter API key for NVIDIA: ")

from langchain.chat_models import init_chat_model

model = init_chat_model("meta/llama3-70b-instruct", model_provider="nvidia")

