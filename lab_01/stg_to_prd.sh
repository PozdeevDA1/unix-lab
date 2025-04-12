#!/bin/bash
git checkout prd
git merge stg
git tag "prd-$(date +%Y%m%d%H%M)"
git push origin prd --tags
