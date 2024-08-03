# GitHub Actions

Durante lo sviluppo di software, spesso vengono utilizzati strumenti di automazione per eseguire azioni ripetitive e ridurre il carico di lavoro degli sviluppatori. GitHub, piattaforma di sviluppo software basata su Git, mette a disposizione degli strumenti che permettono di automatizzare il flusso di lavoro: le GitHub Actions.

Una GitHub Action è un'automazione basata su eventi, ovvero una serie di comandi che vengono eseguiti quando si verfica un evento specifico. Gli eventi possono essere vari, nel caso in esame il trigger è la creazione di una pull request.

Le GitHub Actions sfruttano i workflow per definire le automazioni, ossia un file che specifica quali azioni devono essere eseguite in risposta a determinati eventi. I workflow sono definiti attraverso i file YAML (.yml) e posizionati all'interno della directory _.github/workflows_. Quando si verifica l'evento previsto, il workflow viene avviato automaticamente.

## Test eseguito

È stata crata una repository per poter comprendere e sfruttare le GitHub Actions. L'obbiettivo principale è stato quello di creare un'automazione che mi permettese di ottenere un file di changelog ad ogni aggiornamneto delle pull request. La directory _src/_ contiene del codice di prova utile per poter eseguire i diversi test. 

Inizialmente è stato creato il file 'test_action.yml'il cui funzionamento è molto semplice: stampa un messaggio quando ci sono cambiamenti in un qualsiasi file all'interno di _src/_. Questo mi ha permesso di comprendere i principi fondamentali delle GitHub Actions.

Solo in seguito, ho sviluppato e tastato 'generate_changelog.yml'. Questo file automatizza la generazione di un file di changelog che riassume le modifiche apportate.

### Fonti consultate

T. Kinsman, M. Wessel, M. A. Gerosa, and C. Treude, “How do software developers use github actions to automate their workflows?,” in Proceedings - 2021 IEEE/ACM 18th International Conference on Mining Software Repositories, MSR 2021, 2021. doi: 10.1109/MSR52588.2021.00054.

https://docs.github.com/en/actions/about-github-actions/understanding-github-actions