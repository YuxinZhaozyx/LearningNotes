# Git Operation
## git

		git --help

## git init

		git init

## git add

		git add <file>
>可添加多个文件    
		git add * 
>添加工作目录下所有文件  

## git commit

		git commit -m "add a README file"

		git commit --amend 
>更改最近一次commit的信息  
>进入一个新的窗口，在该窗口下修改  
>按i键进行insert，按ESC退出insert，按Shift+Z(双击)保存并退出，输入:q!退出不保存  

		git commit --amend -m "add a README FILE"
>只更改最近一次commit的信息，不进入新窗口  

## git status

		git status

## git reset
>git reset命令同时移动HEAD指针和HEAD指向的分支的指针  
>git reset的所有指令（除单独回滚文件的命令外）都会导致HEAD所在分支中不属于其他分支和以指定的快照为HEAD（如HEAD~）的分支的所有快照被删除  

		git reset HEAD <file>  
>回退最近的一步操作  
		git reset HEAD

		git reset HEAD~
>回到上一版本，HEAD指向发生变化  
		git reset HEAD~~
>回到上上个版本  
		git reset HEAS~2 
>效果同上，回退到上上个版本  

		git reset --mixed HEAD~
>移动HEAD的指向，将其指向上一个快照（回滚Git仓库）  
>将HEAD移动后指向的快照回滚到暂存区域（回滚暂存区域）  
>不加--mixed默认为mixed  

		git reset --soft HEAD~
>移动HEAD的指向，将其指向上一个快照(回滚Git仓库)

		git reset --hard HEAD~
>移动HEAD的指向，将其指向上一个快照（回滚Git仓库）  
>将HEAD移动后指向的快照回滚到暂存区域（回滚暂存区域）  
>将暂存区域的文件还原到工作目录（回滚工作目录）  

		git reset [--mixed]/[--soft]/[--hard] <branch>
>直接移动到指定分支，删除原分支  

		git reset 87bfbe8b 
>通过指定要回退版本的哈希值（ID号）回滚(也可以向前滚，只要有对应快照的哈希值即可，可用git log -g找到（q键退出git log -g模式）)  
>假定哈希值是87bfbe8b87386c0cd6a639bd833ba887f2fcc6fb，只需指定前数个数字  
>哈希值可用git log查到  
>由于默认为mixed，所以对工作目录里的文件无影响，可改用--hard  

		git reset 86bfbe8b <file>/<path>
>回滚指定版本快照里的指定文件，但HEAD不移动  

## git checkout

		git checkout -- <file> 
>用暂存区域的指定文件覆盖当前工作目录里的该文件  

		git checkout <file> 
>同上，用暂存区域的指定文件覆盖当前工作目录里的该文件  
>上一方法加--只是为了防止恰好有分支的名字跟指定的文件相同  
>推荐用git checkout -- <file>  

		git checkout <快照ID> <file> 
>用指定快照里的指定文件覆盖当前工作目录和暂存区域里的该文件  

		git checkout <branch> 
>切换到指定分支上，将HEAD指向指定分支  
>切换分支后工作目录、暂存区域和Git仓库都会变化到该分支下的状态  

		git checkout -b <branch>
>创建并切换到一个新的分支  

## git log

		git log 
>查看最近commit的文件和信息,按q提前退出  

		git log --oneline
>简化版本的git log，只显示快照ID的前7位和快照提交时的信息  

		git log --graph
>以图形化形式显示分支，一般与--all结合使用  

		git log --all
>显示所有分支,不加all只显示当前分支的快照记录  

## git diff

		git diff
>比较不同的文件  

		git diff 快照ID 快照ID 
>比较两个快照  

		git diff 快照ID 
>比较当前工作目录与指定快照的Git仓库  

		git diff --cached 快照ID 
>比较暂存区域与指定快照的Git仓库  

## git rm

		git rm <file>  
>当工作目录和暂存区域中的指定文件相同时，删除工作目录和暂存区域的指定文件，不删除快照中的该文件,可用git commit --amend修改快照  
>可通过git reset HEAD <file> 将该文件恢复到暂存区域，再用git checkout -- <file> 将文件恢复到工作目录，也可用git reset --hard HEAD直接恢复工作目录和暂存区域  

		git rm --cached <file>
>只删除暂存区域的指定文件，不删除工作目录和快照的该文件  

		git rm -f <file>
>强制删除工作目录和暂存区域的指定文件，不理会两文件是否相同  

## git mv

		git mv <file name1> <file name2>
>将工作目录、暂存区域和快照中的file name1都重命名为file name2  
>可用git commit --amend后不做修改直接退出确定将快照中的文件改成指定名字  

## git branch 

		git branch <new branch>
>创建新的分支，<new branch>为新分支名  

		git branch -d <branch> 或 git branch --delete <branch>
>删除指定分支  
>当该分支已合并时，只删除了指向分支的指针，分支本身的快照依旧存在  
>当该分支未合并时，删除分支的指针和属于该分支而不与其他分支重合的快照  

## git merge

		git merge <branch>
>将当前分支与指定分支合并

## git config

		git config --global user.name "my name"
>修改用户名  

		git config --global user.email "1111111111@qq.com"
>修改邮箱  

		git config --list
>查看所有设置  

## git clone 

		git clone <repository address>
>复制远程git仓库，repository address从github获得  

## git push

		git push
>将本地仓库与远程仓库同步，需要先设置好user.name和user.email  