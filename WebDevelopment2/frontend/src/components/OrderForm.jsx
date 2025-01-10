import Button from "react-bootstrap/Button";
import Form from "react-bootstrap/Form";
import { useState, useEffect } from "react";
import Card from 'react-bootstrap/Card';
import ListGroup from 'react-bootstrap/ListGroup';
import { URL } from "../Utils/constants";

export const OrderForm = () => {
    const [sandwiches, setSandwiches] = useState([]);
    const [activeSandwich, setActiveSandwich] = useState({});
    const [isLoading, setLoading] = useState(false);

    useEffect(() => {
        const fetchSandwiches = async () => {
            try {
                const response = await fetch(URL + "/sandwich");
                const data = await response.json();
                setSandwiches(data);
                setActiveSandwich(data[0]); // Set active sandwich to the first one by default
            } catch (error) {
                console.error('Error fetching sandwiches:', error);
            }
        };

        fetchSandwiches();
    }, []); // Empty dependency array to fetch sandwiches only once when component mounts

    const handleChange = (e) => {
        const selectedSandwich = sandwiches.find(sandwich => sandwich.name === e.target.value);
        setActiveSandwich(selectedSandwich);
    };

    const handleSubmit = async (e) => {
        e.preventDefault();
        setLoading(true);
        const resp = await fetch(URL + "/order", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify({
                id: 0,
                sandwichId: activeSandwich.id,
                status: "ordered"
            })
        });

        setLoading(false); // Regardless of response status, loading should be set to false

        if (resp.status === 200) {
            // Handle successful response
        } else {
            // Handle error response
        }
    };

    return (
        <div>
            <Form>
                <Form.Select style={{ width: '18rem' }} value={activeSandwich.name || ''} onChange={handleChange}>
                    {sandwiches.map((sandwich, i) => (
                        <option key={i} value={sandwich.name}>
                            {sandwich.name}
                        </option>
                    ))}
                </Form.Select>
            </Form>
            <Card style={{ width: '18rem' }}>
                <ListGroup>
                    <ListGroup.Item>{"Name: " + activeSandwich.name}</ListGroup.Item>
                    <ListGroup.Item>{"Bread type: " + activeSandwich.breadType}</ListGroup.Item>
                    <ListGroup.Item>{"Toppings: " + (activeSandwich.Toppings ? activeSandwich.Toppings.map(t => t.name) : '')}</ListGroup.Item>
                </ListGroup>
            </Card>
            <Button disabled={isLoading} type="submit" variant="primary" onClick={handleSubmit}>Create order</Button>
        </div>
    );
};
