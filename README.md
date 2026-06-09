
# Estruturas de Dados Avançadas: Árvores Binárias, N-Árias e AVL

👥 Integrantes do Grupo

* Francisco Francivaldo
* Pedro Arthur
* Ezequias Menezes
* Yasmin Rodrigues
* Evelyn Barbosa

## 📝 Descrição do Projeto

Este projeto consiste no desenvolvimento e aperfeiçoamento de estruturas de dados baseadas em árvores. O objetivo principal foi implementar modificações técnicas específicas para gerenciar valores duplicados, realizar remoções complexas em estruturas N-árias e garantir o auto-balanceamento dinâmico através de árvores AVL.

Cada modificação foi projetada para otimizar o uso da memória, corrigir falhas de execução e manter a integridade das estruturas de dados sob diferentes cenários operacionais.


## 🛠️ Detalhes da Implementação

### 1. Árvore Binária de Pesquisa (ABP) com Valores Repetidos

Adaptada para permitir e gerenciar chaves duplicadas sem corromper a lógica de busca e sem perder referências de memória no menu interativo.

 
**Inserção de Duplicados**: Quando um valor igual a um já existente é inserido, o fluxo direciona o elemento obrigatoriamente para a subárvore direita, permitindo o empilhamento de chaves idênticas.

 
**Busca Corrigida**: Durante a busca de um nó para remoção, se houver chaves duplicadas, o algoritmo desce estritamente pelo ramo direito para mapear o ponteiro do pai atualizado.

 
**Remoção por Ponteiro**: A remoção foi alterada para realizar a checagem baseada na identidade do ponteiro na memória (e não pelo valor da chave). Isso garante que, se pai e filho tiverem o mesmo valor, o algoritmo saiba exatamente qual braço desconectar, removendo uma instância por vez.

 
**Correção no Menu**: Correção de um erro crítico onde a busca sobrescrevia a raiz do programa com o nó encontrado (`ABPmain.c`). O resultado foi redirecionado para um ponteiro auxiliar (`p_aux`), mantendo a árvore íntegra.

## 2. Remoção Complexa em Árvores N-Árias

Implementação de funções para a deleção de nós em árvores N-árias estruturadas com a técnica de **"Filho Esquerdo, Irmão Direito"**. O sistema oferece duas opções para a remoção:

 
**Modo 1 (Cascata)**: Isola o nó alvo da lista do pai e desaloca recursivamente (via caminhamento pós-ordem) o nó selecionado e todas as suas subárvores descendentes, evitando vazamentos de memória (*Memory Leak*).

 
**Modo 2 (Promoção)**: Isola o nó alvo e faz com que o "avô" adote os "netos". O último elemento da lista de filhos do nó alvo é reconectado para apontar diretamente para os antigos filhos do avô.

## 3. Árvore AVL com Auto-Balanceamento Dinâmico

Implementação de uma estrutura que se auto-balanceia de forma dinâmica com base nos fatores de balanceamento ($FB \in \{-1, 0, 1\}$).

 
**Compatibilidade**: Correção do erro crítico `typedef int bool` que gerava colisão em compiladores modernos (como VS Code / C++84), substituindo-o pela inclusão nativa `<stdbool.h>` no cabeçalho `AVL.h`.

 
**Rotações Automáticas**: Aplicação de rotações simples (direta/esquerda) ou duplas nas operações de escrita sempre que a estrutura fica desbalanceada (ex: quando um braço fica pesado com $FB = -2$).


**Eficiência Garantida**: As funções de inserção e remoção atualizam a altura de cada nó visitado durante o desempilhamento da recursão. Caso detectem desbalanceamento, executam a rotação apropriada. Isso assegura que a complexidade matemática de busca permaneça otimizada em $O(\log n)$.
