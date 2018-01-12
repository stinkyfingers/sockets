package main

import (
	"log"
	"syscall"
)

func main() {
	log.Print("Running")
	domain := syscall.AF_LOCAL
	typ := syscall.SOCK_STREAM
	proto := 0

	name := "/tmp/fast.sock"

	// socket
	fd, err := syscall.Socket(domain, typ, proto)
	if err != nil {
		log.Fatal(err)
	}

	// bind
	syscall.Unlink(name)
	sa := &syscall.SockaddrUnix{}
	sa.Name = name

	err = syscall.Bind(fd, sa)
	if err != nil {
		log.Fatal("bind ", err)
	}

	err = syscall.Listen(fd, 5)
	if err != nil {
		log.Fatal("listen ", err)
	}

	for {
		buf := make([]byte, 1024) // TODO - make growable buffer or io.copy
		log.Print("FOR")
		cl, _, err := syscall.Accept(fd)
		if err != nil {
			log.Fatal("accept ", err)
		}
		for {
			rc, err := syscall.Read(cl, buf)
			if err != nil {
				log.Fatal("read ", err)
			}

			if rc == 0 {
				log.Print("close")
				syscall.Close(cl)
			}
			log.Print(string(buf))
		}
	}

	syscall.Close(fd)
	syscall.Unlink(name)

}
