#!/bin/sh
id -G -n $FT_USER | sed -e "s/ /,/g"
