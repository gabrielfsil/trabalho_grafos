# trabalho_grafos

## GIT TUTORIAL
### Primeira configuração

- Crie um clone do repositório: git clone <link-para-o-repositorio>

- Entre na pasta criada pelo comando clone: cd /nomeDoRepositório

- Crie sua branch usando como o padrão o nome da feature que você está a desenvolver: git checkout -b tad_aluno
### Rotina
- Adicione as alterações feitas: git add .

- Cheque em qual branch está e quais alterações foram adicionadas: git status

- Dê um commit com uma mensagem especificando as alterações realizadas: git commit -m "mensagem especificando o que foi feito"

- Envie o commit feito para sua branch: git push origin suabranch

### Quando estiver tudo prontinho
- Volte para a master: git checkout master

- Atualize a master: git pull

- Volte para a sua branch: git checkout nomedabranch

- Mescle a master com a sua branch : git merge master

- Confirme o merge : git push origin suabranch


- Volte para a master: git checkout master

- Mescle a master com as alterações enviadas para sua branch : git merge suabranch

- Confirme o merge : git push origin master

### Atualizar (Sempre que entrar para desenvolver)
- Para atualizar a master: git pull

- Para atualizar alguma branch: git pull origin branch
