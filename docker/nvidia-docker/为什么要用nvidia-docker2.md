### 最简单的原因
因为`nvidia-docker1`被nvidia标记为废弃了, 官方都废弃了, 我们还在用, 那就是自己给自己挖坑.

### nvidia-docker1的原理
`nvidia-docker`作为docker的一个封装, 需要运行一个独立的`daemon`, 与Docker的生态不能很好的兼容.

比如:
1. docker-compose
2. docker-swarm
3. kunbernetes

### nvidia-docker2
1. nvidia-docker1是一个volume plugin
2. nvidia-docker2是一个docker runtime


### RHEL-based distributions
```
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.repo | \
  sudo tee /etc/yum.repos.d/nvidia-docker.repo
```

这里干了啥呢, 主要是从nvidia官网拉下来一个`nvidia-docker.repo`

### 配置nvidia-docker2
/etc/docker/daemon.json
```json
{
    "runtimes": {
        "nvidia": {
            "path": "nvidia-container-runtime",
            "runtimeArgs": []
        }
    },
    "default-runtime": "nvidia",
    ...
}
```
如果没有配置.加一个`--runtime`参数也可以启动
```
docker run --runtime nvidia ...
```
