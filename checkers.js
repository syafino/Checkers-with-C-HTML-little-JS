console.log("JavaScript loaded");

function loadBoard() {
    fetch('checkers.cgi')
        .then(response => response.text())
        .then(data => {
            const boardDiv = document.createElement('div');
            boardDiv.innerHTML = data;

            // Try multiple ways to get board state
            const dataAttrState = boardDiv.querySelector('#board')?.getAttribute('data-board-state');
            const hiddenInputState = boardDiv.querySelector('#currentBoardState')?.value;

            console.log('Data from server:', data);
            console.log('Data attribute state:', dataAttrState);
            console.log('Hidden input state:', hiddenInputState);

            const boardState = dataAttrState || hiddenInputState;

            if (boardState) {
                document.getElementById('board').innerHTML = data;
                document.getElementById('boardAsString').value = boardState;
                document.getElementById('currentBoardState').value = boardState;
                console.log('Board state set successfully:', boardState);
            } else {
                console.error('No board state found in server response');
            }
        })
        .catch(error => console.error('Error loading board:', error));
}

function submitMove(event) {
    event.preventDefault();
    
    // Get form data
    const form = document.getElementById('moveForm');
    const formData = new FormData(form);
    
    // Get the board state
    const boardState = document.getElementById('currentBoardState').value;
    formData.set('boardAsString', boardState);
    
    // Convert FormData to URL-encoded string
    const urlEncodedData = new URLSearchParams(formData).toString();
    
    console.log("Sending data:", urlEncodedData);
    
    fetch('update_board.cgi', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded'
        },
        body: urlEncodedData
    })
    .then(response => response.text())
    .then(data => {
        console.log('Received data:', data);
        const boardDiv = document.createElement('div');
        boardDiv.innerHTML = data;
        const newBoard = boardDiv.querySelector('#board');
        if (newBoard) {
            document.getElementById('board').innerHTML = newBoard.innerHTML;
            const newState = newBoard.getAttribute('data-board-state');
            if (newState) {
                document.getElementById('currentBoardState').value = newState;
                document.getElementById('boardAsString').value = newState;
            }
        } else {
            console.error('No board element found in response');
        }
    })
    .catch(error => {
        console.error('Error:', error);
    });
}

window.onload = loadBoard;
