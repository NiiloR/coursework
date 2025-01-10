import Table from "react-bootstrap/Table";
import { useEffect } from "react";
import { URL, POLL_INTERVAL } from "../Utils/constants";
import { useState } from "react";
import { useParams } from "react-router-dom";

export const OrderTable = () => {
    const [orders, setOrders] = useState([]);
    const { id } = useParams();

    useEffect(() => {
        const fetchData = async () => {
            try {
                const response = id ? await fetch(URL + "/order/" + id) : await fetch(URL + "/order/")
                const data = await response.json();
                setOrders(id ? [data] : data);
            } catch (error) {
                console.error("Error fetching data:", error);
                setOrders([])
            }
        };

        // Fetch data initially
        fetchData();

        // Fetch data every 5 seconds
        const intervalId = setInterval(fetchData, POLL_INTERVAL);

        // Clean up interval
        return () => clearInterval(intervalId);
    }, [id]); 

    const orderData = orders.map((order, index) => {
        return <tr key={index}>
            <td>{order.id}</td>
            <td>{order.status}</td>
        </tr>
    })
    if (orders.length === 0) {
        return (
            <div>
                Order(s) not found.
            </div>
        )
    }
    return (
        <Table bordered striped hover >
            <thead>
                <tr>
                    <th>Order id</th>
                    <th>Order status</th>
                </tr>
            </thead>
            <tbody>
                {orderData}
            </tbody>
        </Table>
    );
}