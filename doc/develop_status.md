# Summary

|                       | file        | header   | methods  | test     |
|-----------------------|-------------|----------|----------|----------|
| type defines          | Basic       | &#x2714; |          |          |
| basic error           | Basic       | &#x2714; | &#x2714; |          |
|                       |             |          |          |          |
| *Basic Type*          |             |          |          |          |
| String                | String      | &#x2714; | &#x2714; | &#x2714; |
| Date                  | DateTime    | &#x2714; | &#x2714; | &#x2714; |
| Time                  | DateTime    | &#x2714; | &#x2714; | &#x2714; |
| DateTime              | DateTime    | &#x2714; | &#x2714; | &#x2714; |
| Log                   | Log         | &#x2714; | &#x2714; | &#x2714; |
| StaticDict            | Dict        | &#x2714; | &#x2714; | &#x2714; |
| DynamicDict           | Dict        | &#x2714; | &#x2714; | &#x2714; |
| Sheet                 | Dict        | &#x2714; | &#x2714; | &#x2714; |
|                       |             |          |          |          |
| *General Array Type*  |             |          |          |          |
| Vector                | Vector      |          |          |          |
| Array                 | Array       |          |          |          |
| TypeArray Template    |             |          |          |          |
|                       |             |          |          |          |
| *Int Arrays*          |             |          |          |          |
| IntVector             | IntVector   |          |          |          |
| IntMatrix             | IntMatrix   |          |          |          |
| IntTensor             |             |          |          |          |
| IntArray              |             |          |          |          |
|                       |             |          |          |          |
| *Float Arrays*        |             |          |          |          |
| FloatVector           | FloatVector |          |          |          |
| FloatMatrix           | FloatMatrix |          |          |          |
| FloatTensor           |             |          |          |          |
| FloatArray            |             |          |          |          |
|                       |             |          |          |          |
| *Macro Template*      |             |          |          |          |
| IntVector_n macro     | IntVectorF  |          |          |          |
| IntMatrix_m_n macro   | IntMatrixF  |          |          |          |
| IntTensor_p_q_r macro |             |          |          |          |

# Depencency

| Module      | String | DateTime | IntVector |        |
|-------------|--------|----------|-----------|--------|
| Basic       |        |          |           |        |
| String      |        |          |           |        |
| DateTime    | String |          |           |        |
| Log         | String | DateTime |           |        |
| Dict        | String |          |           |        |
| Vector      |        |          |           |        |
| Array       |        |          |           | Vector |
| IntVector   |        |          |           |        |
| IntMatrix   |        |          | IntVector |        |
| FloatVector |        |          | IntVector |        |
| FloatMatrix |        |          | IntVector |        |

# By file

## DateTime
