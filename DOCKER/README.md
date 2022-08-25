# Docker example


## Build 
```
docker build -t electrocomms .
```
## Run interactively
```
docker run  --rm -it --name electrocomms electrocomms
```

## Start server (background)
```
./electrocomms 8080 > /dev/null 2>&1 &
```
## Start client
```
./electrocomms 127.0.0.1 8080
```

## Start integrated demo
```
cd ../demo/integrated

node server &
node client
```