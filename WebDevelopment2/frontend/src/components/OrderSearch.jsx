
import Navbar from 'react-bootstrap/Navbar';
import Form from 'react-bootstrap/Form';
import Button from 'react-bootstrap/Button';
import Row from 'react-bootstrap/Row';
import Col from 'react-bootstrap/Col';
import { useNavigate, Link } from 'react-router-dom';

import { useState } from 'react';
import Container from 'react-bootstrap/Container';
import Nav from 'react-bootstrap/Nav';

export const OrderSearch = () => {
    const navigate = useNavigate()
    const [id, setId] = useState("")
    const handleSubmit = (e) => {
        e.preventDefault()
        setId("")
        navigate("/orders/" + id)
    }
    const handleChange = (e) => {
        setId(e.target.value)
        console.log(id)
    }
    return (
        <Navbar className="bg-body-tertiary">
            <Nav className="me-auto">
                <Link to="/orders" className="nav-link">All orders</Link>
                <Link to="/create" className="nav-link">Create order</Link>
            </Nav>
            <Form inline="true" onSubmit={handleSubmit}>
                <Row>
                    <Col xs="auto">
                        <Form.Control
                            type="text"
                            placeholder="orderId"
                            className=" mr-sm-2"
                            onChange={handleChange}
                            value={id}
                        />
                    </Col>
                    <Col xs="auto">
                        <Button type="submit">Search</Button>
                    </Col>
                </Row>
            </Form>
        </Navbar>
    )
}