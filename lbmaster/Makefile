#file=lbm.go
file=streamming.go
#file=imcompletes.go

rpi: ${file}
	GOARM=7 GOARCH=arm GOOS=linux go build ${file}

build:
	go build ${file}

install:
	go install ${file}
