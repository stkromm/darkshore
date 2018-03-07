
const fs = require('fs');
const path = require('path');


function readdir(dirname) {
    fs.readdir(dirname, (err, files) => {
    if( err ) {
        console.error( "Could not list the directory.", err );
        process.exit( 1 );
    } 

    files.forEach( function( file, index ) {
            // Make one pass and make the file complete
            var fromPath = path.join( dirname, file );

            fs.stat( fromPath, function( error, stat ) {
                if( error ) {
                    console.error( "Error stating file.", error );
                    return;
                }

                if( stat.isFile() )
                    console.log( "'%s' is a file.", fromPath );
                else if( stat.isDirectory() )
                    console.log( "'%s' is a directory.", fromPath );
                    readdir(fromPath)
                });
    } );
})};

readdir('../res/');