// ============================
// 1. SELECT DOM ELEMENTS
// ============================
const input = document.getElementById('task-input');
const addBtn = document.getElementById('add-task-btn');
const listA = document.getElementById('pending-tasks');
const listB = document.getElementById('completed-tasks');
const countA = document.getElementById('pending-count');
const countB = document.getElementById('completed-count');


// ============================
// 2. HELPERS
// ============================
function updateCounts() {
    countA.textContent = `(${listA.children.length})`;
    countB.textContent = `(${listB.children.length})`;
}

function resetInput() {
    input.value = '';
    addBtn.disabled = true;
}


// ============================
// 3. CREATE LIST ITEM
// ============================
function createItem(text, completed = false) {
    const li = document.createElement('li');

    const span = document.createElement('span');
    span.textContent = text;

    const toggleBtn = document.createElement('button');
    toggleBtn.textContent = completed ? 'Back' : 'Done';

    toggleBtn.addEventListener('click', () => {
        if (completed) {
            listA.appendChild(li);
            toggleBtn.textContent = 'Done';
            completed = false;
        } else {
            listB.appendChild(li);
            toggleBtn.textContent = 'Back';
            completed = true;
        }
        updateCounts();
    });

    const deleteBtn = document.createElement('button');
    deleteBtn.textContent = 'Delete';

    deleteBtn.addEventListener('click', () => {
        li.remove();
        updateCounts();
    });

    li.append(span, toggleBtn, deleteBtn);
    return li;
}


// ============================
// 4. ADD ITEM
// ============================
function addItem() {
    const text = input.value.trim();
    if (text.length < 5) return;

    const item = createItem(text);
    listA.appendChild(item);
    updateCounts();
    resetInput();
}

addBtn.addEventListener('click', addItem);


// ============================
// 5. VALIDATION (OPTIONAL)
// ============================
input.addEventListener('input', () => {
    addBtn.disabled = input.value.trim().length < 5;
});


// ============================
// 6. LOAD JSON (OPTIONAL)
// ============================
async function loadData() {
    listA.innerHTML = '';
    listB.innerHTML = '';

    const response = await fetch('data.json');
    const data = await response.json();

    data.forEach(item => {
        const el = createItem(item.text, item.completed);
        item.completed ? listB.appendChild(el) : listA.appendChild(el);
    });

    updateCounts();
}
