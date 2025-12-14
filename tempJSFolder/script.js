// DOM Elements
const taskInput = document.getElementById('task-input');
const taskDate = document.getElementById('task-date');
const addTaskBtn = document.getElementById('add-task-btn');
const loadTasksBtn = document.getElementById('load-tasks-btn');
const pendingTasksList = document.getElementById('pending-tasks');
const completedTasksList = document.getElementById('completed-tasks');
const pendingCount = document.getElementById('pending-count');
const completedCount = document.getElementById('completed-count');

// Initial state
addTaskBtn.disabled = true;

// --------------------
// Helper functions
// --------------------
function updateCounts() {
    pendingCount.textContent = `(${pendingTasksList.children.length})`;
    completedCount.textContent = `(${completedTasksList.children.length})`;
}

function resetInput() {
    taskInput.value = '';
    taskDate.value = '';
    taskInput.classList.remove('valid', 'invalid');
    addTaskBtn.disabled = true;
}

function createTaskElement(text, date, completed = false) {
    const li = document.createElement('li');

    const textSpan = document.createElement('span');
    textSpan.textContent = text;

    li.appendChild(textSpan);

    if (date) {
        const dateSpan = document.createElement('span');
        dateSpan.className = 'task-date';
        dateSpan.textContent = date;
        li.appendChild(dateSpan);
    }

    const toggleBtn = document.createElement('button');
    toggleBtn.textContent = completed ? 'Върни' : 'Завърши';

    toggleBtn.addEventListener('click', () => {
        if (completed) {
            pendingTasksList.appendChild(li);
            toggleBtn.textContent = 'Завърши';
            completed = false;
        } else {
            completedTasksList.appendChild(li);
            toggleBtn.textContent = 'Върни';
            completed = true;
        }
        updateCounts();
    });

    const deleteBtn = document.createElement('button');
    deleteBtn.textContent = 'Изтрий';
    deleteBtn.className = 'delete-btn';

    deleteBtn.addEventListener('click', () => {
        li.remove();
        updateCounts();
    });

    li.appendChild(toggleBtn);
    li.appendChild(deleteBtn);

    return li;
}

// --------------------
// Validation
// --------------------
taskInput.addEventListener('input', () => {
    const value = taskInput.value.trim();

    if (value.length < 5) {
        taskInput.classList.add('invalid');
        taskInput.classList.remove('valid');
        addTaskBtn.disabled = true;
    } else {
        taskInput.classList.add('valid');
        taskInput.classList.remove('invalid');
        addTaskBtn.disabled = false;
    }
});

// --------------------
// Add task
// --------------------
function addTask() {
    const text = taskInput.value.trim();
    if (text.length < 5) return;

    const date = taskDate.value;
    const taskElement = createTaskElement(text, date);

    pendingTasksList.appendChild(taskElement);
    updateCounts();
    resetInput();
}

addTaskBtn.addEventListener('click', addTask);

taskInput.addEventListener('keydown', (e) => {
    if (e.key === 'Enter' && !addTaskBtn.disabled) {
        addTask();
    }
});

// --------------------
// Load tasks from JSON
// --------------------
loadTasksBtn.addEventListener('click', async () => {
    pendingTasksList.innerHTML = '';
    completedTasksList.innerHTML = '';

    try {
        const response = await fetch('tasks.json');
        const tasks = await response.json();

        tasks.forEach(task => {
            const taskElement = createTaskElement(
                task.text,
                task.date || '',
                task.completed
            );

            if (task.completed) {
                completedTasksList.appendChild(taskElement);
            } else {
                pendingTasksList.appendChild(taskElement);
            }
        });

        updateCounts();
        resetInput();
    } catch (err) {
        console.error('Error loading tasks:', err);
    }
});
