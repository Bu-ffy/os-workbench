export COURSE=OS2021
export MODULE=M1
export TOKEN=L7JyUzHc

FILE=/tmp/upload.tar.bz2
tar caf "$FILE" ".git" $(find . -maxdepth 1 -name "*.pdf") && \
  curl -F "token=$TOKEN" \
       -F "course=$COURSE" \
       -F "module=$MODULE" \
       -F "file=@$FILE" \
       http://192.168.31.224:5000/upload

