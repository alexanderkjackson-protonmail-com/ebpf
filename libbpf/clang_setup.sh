#!/bin/bash
echo "CompileFlags:
  Add: [-I/usr/lib/modules/$(uname -r)/build]" > .clangd
