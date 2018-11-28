function ccat() {
    local style="monokai"
    if [ $# -eq 0 ]; then
        pygmentize -P style=$style -P tabsize=4 -f terminal256 -g
    else
        for NAME in $@; do
            pygmentize -P style=$style -P tabsize=4 -f terminal256 -g "$NAME"
        done
    fi
}

#作者：韦易笑
#链接：https://zhuanlan.zhihu.com/p/49552439
#来源：知乎
#著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
