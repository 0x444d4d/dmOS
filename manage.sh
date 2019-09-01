#! /bin/bash
WDIR=$(pwd)
VDIR="/home/david/Documents/VagrantBoxes/Debian/"
VSTATE=0

state () {
    VSTATE=$(vagrant status | grep -c -m 1 "running")
    return
}

emulate () {

    qemu-system-i386 -fda os-image.bin
    return
}

get () {

    state
    if [ $VSTATE == "0" ]; then
        vagrant up
    fi
    vagrant scp default:/home/vagrant/OS/bin/os-image.bin .
    return
}

startm () {
    state
    if [ $VSTATE == "1" ]; then
        echo "VM already powered on"
        return
    fi
    echo "Booting up the VM"
    vagrant halt
    return
}

stopm () {
    state
    if [ $VSTATE == "0" ]; then
        echo "VM already powered off"
        return
    fi
    echo "Shuting down the VM"
    vagrant halt
    return
}

program () {
    state
    if [ $VSTATE == "0" ]; then
        vagrant up
    fi
    vagrant ssh
    return
}

compile () {
    state
    if [ $VSTATE == "0" ]; then
        vagrant up
    fi
    vagrant ssh -c 'cd OS && make'
    return

}

$WDIR=$(pwd)
cd $VDIR
while [ "$1" != "" ]; do
    case $1 in 
        e | emulate )
            emulate
            shift
            ;;
        p | program )
            program
            shift
            ;;
        c | compile )
            compile
            shift
            ;;
        g | get )
            get
            shift
            ;;
        s | stop )
            stopm
            shift
            ;;
        st | start )
            startm
            shift
            ;;
        * )
            exit 1
    esac
done
cd $WDIR
exit 0

