window.addEventListener('DOMContentLoaded', () => {
    const form = document.querySelector('#dataForm');
    const input = document.querySelector('#dataInput');
    const output = document.querySelector('.output');

    form.addEventListener('submit', async (e) => 
    {
        e.preventDefault();

        const value = input.value.trim();
        try 
        {
            const response = await fetch('http://localhost:8080/api/submit', {
                method: 'POST',
                headers: {
                    'Content-Type' : 'application/json'
                },
                body: JSON.stringify(value),
            });

            const result = await response.json();
            console.log('Server response:', result);
            output.textContent = result.message;
        }
        catch (error)
        {
            console.error('Error:', error);
            output.textContent = 'An error occurred while submitting';
        }
        input.value = ''; // Clear the input field
    }
);
});
