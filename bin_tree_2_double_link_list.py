def func(T):
    if T:
        func(T.left)
        pre = T.left
        while pre and pre.right:
            pre = pre.right
        T.left = pre
        if pre:
            pre.right = T
        func(T.right)
        post = T.right
        while post and post.left:
            post = post.left
        T.right = post
        if post:
            post.left = T
