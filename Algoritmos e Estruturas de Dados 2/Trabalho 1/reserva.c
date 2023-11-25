 //usar para remover "> -"
                textProcessingInputKey(input);
                textProcessing(input, tempLine);
                
                //verifica onde o elemtento inserido e qual sua posicao.
                assistant = searchTrieRecursive(Trie, tempLine, strlen(tempLine), 0);
                
                //utilizar funcao de busca para retornar onde esta a struct
                printf("Removido (%s|%s|%s)\n", data[assistant].id, data[assistant].name, data[assistant].age);

                // Retrocede os elementos da struct que estao a frente da posicao removida se necessario
                for(i = assistant; i <= lines; i++){
                    //if((i+1)<=lines)
                    removeKeyRecursive(&Trie, data[i+1].id, strlen(data[i+1].id), 0);
                    data[i] = data[i+1];
                    insertTrieRecursive(Trie, &(data[i].id[0]), i, strlen(&(data[i].id[0])), 0);
                }
                //realoca a struct na memoria com o novo tamanho.
                lines -= 1;
                data=(dataUser*) realloc(data,(lines+1)*sizeof(dataUser));
                break;