var canvas = document.getElementById("map-canvas");
var downloadElem = document.getElementById("download-map");
var ctx = canvas.getContext("2d");

var globalWallState = [];
var entities = [];

var playerAdded = false;

var scale = 20;

function AddWalls(event) {
    globalWallState.push({
        x: event.clientX,
        y: event.clientY
    });

    if(globalWallState.length == 2) {
        ctx.beginPath();
        ctx.strokeStyle = 'white';

        ctx.moveTo(globalWallState[0].x, globalWallState[0].y);
        ctx.lineTo(globalWallState[1].x, globalWallState[1].y);

        ctx.stroke();

        entities.push({
            isPlayer: 0,
            coords: [...globalWallState]
        });

        globalWallState = [];
    }
}

function AddPlayer(event) {
    if(!playerAdded) {
        ctx.beginPath();
        ctx.strokeStyle = 'red';

        ctx.arc(event.clientX, event.clientY, 10, 0, 2 * Math.PI);
        ctx.stroke();

        entities.push({
            isPlayer: 1,
            coords: [{ x: event.clientX, y: event.clientY }, { x: 0, y: 0 }]
        });

        playerAdded = true;
    }
}

function DownloadMap() {
    let uri = "data:text/plain;charset=utf-8,";

    uri += encodeURIComponent(`${canvas.width} ${canvas.height}`);

    for(let entity of entities) {
        let coords = [
            entity.coords[0].x - canvas.width / 2,
            entity.coords[0].y - canvas.height / 2,
            entity.coords[1].x - canvas.width / 2,
            entity.coords[1].y - canvas.height / 2
        ];

        uri += encodeURIComponent(
            `[${entity.isPlayer}|(${coords[0] / scale} ${coords[1] / scale})|(${coords[2] / scale} ${coords[3] / scale})]`
        );
    }

    downloadElem.setAttribute("href", uri);
}

function Entry() {
    const def = 600;

    canvas.width = parseInt(
        prompt(`Enter the width of your map(defaults to ${def} px).`, def)
    );

    canvas.height = parseInt(
        prompt(`Enter the height of your map(defaults to ${def} px).`, def)
    );

    ctx.fillStyle = 'black';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

    let buttons = document.getElementsByClassName("btn");

    for(let i = 0; i < buttons.length; i++) {
        switch(buttons[i].id) {
        case "walls": 
            buttons[i].onclick = () => canvas.onclick = AddWalls;
            break;
        case "player":
            buttons[i].onclick = () => canvas.onclick = AddPlayer;
            break;
        case "dwld":
            buttons[i].onclick = DownloadMap;
        }
    }
}

Entry();