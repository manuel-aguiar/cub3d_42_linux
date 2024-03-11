#!/usr/bin/env bash

n=1
args_list="$@"

get_arg1()
{
	for arg in "$@"
	do
		if [ "$arg" = "valgrind" ]; then
			echo "$arg";
		fi
	done
}

get_arg2()
{
	for arg in "$@"
	do
		if [ "$arg" = "stderr" ]; then
			echo "stderr";
		fi
	done
}

do_tests()
{
	dir=$1
	test="test"
	chmod +rwx "${dir}${test}${n}.cub";
	echo "${dir}:"
	echo ""
	while [ -e "${dir}${test}${n}.cub" ]; do
		echo ${n}
		if [ -z "$hide" ] ; then
			$val ./cub3D "${dir}${test}${n}.cub"
		else
			$val ./cub3D "${dir}${test}${n}.cub" 2>/dev/null
		fi
		n=$((n+1))
	done
	echo ""
	echo ""
	n=1
}

val=$(get_arg1 ${args_list[@]});
hide=$(get_arg2 ${args_list[@]});
do_tests "invalid_maps/texture_tests/";
do_tests "invalid_maps/color_tests/";
do_tests "invalid_maps/map_tests/";
exit;