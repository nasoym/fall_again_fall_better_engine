
FOLDER=`find projects -maxdepth 1 -mindepth 1 -type d -printf '%f\n' | grep "^$1"`
echo $FOLDER
( cd projects/$FOLDER && ./run.sh )

