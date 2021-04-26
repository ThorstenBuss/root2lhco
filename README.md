# root2lhco

## dependences

* [root](https://root.cern/)

## build

```bash
g++ convert.cc $(root-config --glibs --cflags --libs) -Wall -o convert
```

## run

```bash
./convert <in_file> <out_file> [<nEvents>]
```
