CREATE TABLE Teacher (
    TeacherID INT PRIMARY KEY AUTO_INCREMENT,
    TeacherNumber INT NOT NULL UNIQUE,
    TeacherName VARCHAR(100) NOT NULL,
    PermissionLevel INT NOT NULL,
    PhoneNumber VARCHAR(20),
    OfficeName VARCHAR(100),
    Password VARCHAR(100) NOT NULL
);

CREATE TABLE Classroom (
    RoomID INT PRIMARY KEY AUTO_INCREMENT,
    RoomNumber INT NOT NULL,
    RoomName VARCHAR(100) NOT NULL,
    Capacity INT NOT NULL,
    IsOccupied BOOLEAN NOT NULL DEFAULT FALSE,
    RoomType INT NOT NULL
);
CREATE TABLE BookingRecord (
    BookingID INT PRIMARY KEY AUTO_INCREMENT,
    SubmissionTime DATETIME NOT NULL,
    RoomID INT NOT NULL,
    TeacherID INT NOT NULL,
    BookingDate DATE NOT NULL,
    IsApproved BOOLEAN NOT NULL DEFAULT FALSE,
    FOREIGN KEY (RoomID) REFERENCES Classroom(RoomID),
    FOREIGN KEY (TeacherID) REFERENCES Teacher(TeacherID),
    UNIQUE (RoomID, BookingDate) -- 保证同一日期不会有重复预定
);

INSERT INTO Room (RoomNumber, RoomName, Capacity, IsOccupied, RoomType)
VALUES
(2, '1102', 100, 0, 1),
(3, '1103', 100, 0, 1),
(4, '1104', 100, 0, 1),
(5, '1105', 100, 0, 1),
(6, '1106', 100, 0, 1),
(7, '1107', 100, 0, 1),
(8, '1108', 100, 0, 1),
(9, '1109', 100, 0, 1),
(10, '1110', 100, 0, 1),
(11, '1111', 100, 0, 1),
(12, '1112', 100, 0, 1),
(13, '1113', 100, 0, 1),
(14, '1114', 100, 0, 1),
(15, '1115', 100, 0, 1),
(16, '1116', 100, 0, 1),
(17, '1117', 100, 0, 1),
(18, '1201', 100, 0, 1),
(19, '1202', 100, 0, 1),
(20, '1203', 100, 0, 1),
(21, '1204', 100, 0, 1),
(22, '1205', 100, 0, 1),
(23, '1206', 100, 0, 1),
(24, '1207', 100, 0, 1),
(25, '1208', 100, 0, 1),
(26, '1209', 100, 0, 1),
(27, '1210', 100, 0, 1),
(28, '1211', 100, 0, 1),
(29, '1212', 100, 0, 1),
(30, '1213', 100, 0, 1),
(31, '1214', 100, 0, 1),
(32, '1215', 100, 0, 1),
(33, '1216', 100, 0, 1),
(34, '1217', 100, 0, 1),
(35, '1301', 100, 0, 1),
(36, '1302', 100, 0, 1),
(37, '1303', 100, 0, 1),
(38, '1304', 100, 0, 1),
(39, '1305', 100, 0, 1),
(40, '1306', 100, 0, 1),
(41, '1307', 100, 0, 1),
(42, '1308', 100, 0, 1),
(43, '1309', 100, 0, 1),
(44, '1310', 100, 0, 1),
(45, '1311', 100, 0, 1),
(46, '1312', 100, 0, 1),
(47, '1313', 100, 0, 1),
(48, '1314', 100, 0, 1),
(49, '1315', 100, 0, 1),
(50, '1316', 100, 0, 1),
(51, '1317', 100, 0, 1),
(52, '1401', 100, 0, 1),
(53, '1402', 100, 0, 1),
(54, '1403', 100, 0, 1),
(55, '1404', 100, 0, 1),
(56, '1405', 100, 0, 1),
(57, '1406', 100, 0, 1),
(58, '1407', 100, 0, 1),
(59, '1408', 100, 0, 1),
(60, '1409', 100, 0, 1),
(61, '1410', 100, 0, 1),
(62, '1411', 100, 0, 1),
(63, '1412', 100, 0, 1),
(64, '1413', 100, 0, 1),
(65, '1414', 100, 0, 1),
(66, '1415', 100, 0, 1),
(67, '1416', 100, 0, 1),
(68, '1417', 100, 0, 1),
(69, '2101', 100, 0, 1),
(70, '2102', 100, 0, 1),
(71, '2103', 100, 0, 1),
(72, '2104', 100, 0, 1),
(73, '2105', 100, 0, 1),
(74, '2106', 100, 0, 1),
(75, '2107', 100, 0, 1),
(76, '2108', 100, 0, 1),
(77, '2109', 100, 0, 1),
(78, '2110', 100, 0, 1),
(79, '2111', 100, 0, 1),
(80, '2112', 100, 0, 1),
(81, '2113', 100, 0, 1),
(82, '2114', 100, 0, 1),
(83, '2115', 100, 0, 1),
(84, '2116', 100, 0, 1),
(85, '2117', 100, 0, 1),
(86, '2201', 100, 0, 1),
(87, '2202', 100, 0, 1),
(88, '2203', 100, 0, 1),
(89, '2204', 100, 0, 1),
(90, '2205', 100, 0, 1),
(91, '2206', 100, 0, 1),
(92, '2207', 100, 0, 1),
(93, '2208', 100, 0, 1),
(94, '2209', 100, 0, 1),
(95, '2210', 100, 0, 1),
(96, '2211', 100, 0, 1),
(97, '2212', 100, 0, 1),
(98, '2213', 100, 0, 1),
(99, '2214', 100, 0, 1),
(100, '2215', 100, 0, 1),
(101, '2216', 100, 0, 1),
(102, '2217', 100, 0, 1),
(103, '2301', 100, 0, 1),
(104, '2302', 100, 0, 1),
(105, '2303', 100, 0, 1),
(106, '2304', 100, 0, 1),
(107, '2305', 100, 0, 1),
(108, '2306', 100, 0, 1),
(109, '2307', 100, 0, 1),
(110, '2308', 100, 0, 1),
(111, '2309', 100, 0, 1),
(112, '2310', 100, 0, 1),
(113, '2311', 100, 0, 1),
(114, '2312', 100, 0, 1),
(115, '2313', 100, 0, 1),
(116, '2314', 100, 0, 1),
(117, '2315', 100, 0, 1),
(118, '2316', 100, 0, 1),
(119, '2317', 100, 0, 1),
(120, '2401', 100, 0, 1),
(121, '2402', 100, 0, 1),
(122, '2403', 100, 0, 1),
(123, '2404', 100, 0, 1),
(124, '2405', 100, 0, 1),
(125, '2406', 100, 0, 1),
(126, '2407', 100, 0, 1),
(127, '2408', 100, 0, 1),
(128, '2409', 100, 0, 1),
(129, '2410', 100, 0, 1),
(130, '2411', 100, 0, 1),
(131, '2412', 100, 0, 1),
(132, '2413', 100, 0, 1),
(133, '2414', 100, 0, 1),
(134, '2415', 100, 0, 1),
(135, '2416', 100, 0, 1),
(136, '2417', 100, 0, 1),
(137, '3101', 100, 0, 1),
(138, '3102', 100, 0, 1),
(139, '3103', 100, 0, 1),
(140, '3104', 100, 0, 1),
(141, '3105', 100, 0, 1),
(142, '3106', 100, 0, 1),
(143, '3107', 100, 0, 1),
(144, '3108', 100, 0, 1),
(145, '3109', 100, 0, 1),
(146, '3110', 100, 0, 1),
(147, '3111', 100, 0, 1),
(148, '3112', 100, 0, 1),
(149, '3113', 100, 0, 1),
(150, '3114', 100, 0, 1),
(151, '3115', 100, 0, 1),
(152, '3116', 100, 0, 1),
(153, '3117', 100, 0, 1),
(154, '3201', 100, 0, 1),
(155, '3202', 100, 0, 1),
(156, '3203', 100, 0, 1),
(157, '3204', 100, 0, 1),
(158, '3205', 100, 0, 1),
(159, '3206', 100, 0, 1),
(160, '3207', 100, 0, 1),
(161, '3208', 100, 0, 1),
(162, '3209', 100, 0, 1),
(163, '3210', 100, 0, 1),
(164, '3211', 100, 0, 1),
(165, '3212', 100, 0, 1),
(166, '3213', 100, 0, 1),
(167, '3214', 100, 0, 1),
(168, '3215', 100, 0, 1),
(169, '3216', 100, 0, 1),
(170, '3217', 100, 0, 1),
(171, '3301', 100, 0, 1),
(172, '3302', 100, 0, 1),
(173, '3303', 100, 0, 1),
(174, '3304', 100, 0, 1),
(175, '3305', 100, 0, 1),
(176, '3306', 100, 0, 1),
(177, '3307', 100, 0, 1),
(178, '3308', 100, 0, 1),
(179, '3309', 100, 0, 1),
(180, '3310', 100, 0, 1),
(181, '3311', 100, 0, 1),
(182, '3312', 100, 0, 1),
(183, '3313', 100, 0, 1),
(184, '3314', 100, 0, 1),
(185, '3315', 100, 0, 1),
(186, '3316', 100, 0, 1),
(187, '3317', 100, 0, 1),
(188, '3401', 100, 0, 1),
(189, '3402', 100, 0, 1),
(190, '3403', 100, 0, 1),
(191, '3404', 100, 0, 1),
(192, '3405', 100, 0, 1),
(193, '3406', 100, 0, 1),
(194, '3407', 100, 0, 1),
(195, '3408', 100, 0, 1),
(196, '3409', 100, 0, 1),
(197, '3410', 100, 0, 1),
(198, '3411', 100, 0, 1),
(199, '3412', 100, 0, 1),
(200, '3413', 100, 0, 1),
(201, '3414', 100, 0, 1),
(202, '3415', 100, 0, 1),
(203, '3416', 100, 0, 1),
(204, '3417', 100, 0, 1),
(205, '4101', 100, 0, 1),
(206, '4102', 100, 0, 1),
(207, '4103', 100, 0, 1),
(208, '4104', 100, 0, 1),
(209, '4105', 100, 0, 1),
(210, '4106', 100, 0, 1),
(211, '4107', 100, 0, 1),
(212, '4108', 100, 0, 1),
(213, '4109', 100, 0, 1),
(214, '4110', 100, 0, 1),
(215, '4111', 100, 0, 1),
(216, '4112', 100, 0, 1),
(217, '4113', 100, 0, 1),
(218, '4114', 100, 0, 1),
(219, '4115', 100, 0, 1),
(220, '4116', 100, 0, 1),
(221, '4117', 100, 0, 1),
(222, '4201', 100, 0, 1),
(223, '4202', 100, 0, 1),
(224, '4203', 100, 0, 1),
(225, '4204', 100, 0, 1),
(226, '4205', 100, 0, 1),
(227, '4206', 100, 0, 1),
(228, '4207', 100, 0, 1),
(229, '4208', 100, 0, 1),
(230, '4209', 100, 0, 1),
(231, '4210', 100, 0, 1),
(232, '4211', 100, 0, 1),
(233, '4212', 100, 0, 1),
(234, '4213', 100, 0, 1),
(235, '4214', 100, 0, 1),
(236, '4215', 100, 0, 1),
(237, '4216', 100, 0, 1),
(238, '4217', 100, 0, 1),
(239, '4301', 100, 0, 1),
(240, '4302', 100, 0, 1),
(241, '4303', 100, 0, 1),
(242, '4304', 100, 0, 1),
(243, '4305', 100, 0, 1),
(244, '4306', 100, 0, 1),
(245, '4307', 100, 0, 1),
(246, '4308', 100, 0, 1),
(247, '4309', 100, 0, 1),
(248, '4310', 100, 0, 1),
(249, '4311', 100, 0, 1),
(250, '4312', 100, 0, 1),
(251, '4313', 100, 0, 1),
(252, '4314', 100, 0, 1),
(253, '4315', 100, 0, 1),
(254, '4316', 100, 0, 1),
(255, '4317', 100, 0, 1),
(256, '4401', 100, 0, 1),
(257, '4402', 100, 0, 1),
(258, '4403', 100, 0, 1),
(259, '4404', 100, 0, 1),
(260, '4405', 100, 0, 1),
(261, '4406', 100, 0, 1),
(262, '4407', 100, 0, 1),
(263, '4408', 100, 0, 1),
(264, '4409', 100, 0, 1),
(265, '4410', 100, 0, 1),
(266, '4411', 100, 0, 1),
(267, '4412', 100, 0, 1),
(268, '4413', 100, 0, 1),
(269, '4414', 100, 0, 1),
(270, '4415', 100, 0, 1),
(271, '4416', 100, 0, 1),
(272, '4417', 100, 0, 1);
INSERT INTO Teacher (TeacherNumber, TeacherName, PermissionLevel, PhoneNumber, OfficeName, Password) VALUES
(1001, 'Alice Smith', 1, '1234567890', 'Office A', 'password1'),
(1002, 'Bob Johnson', 2, '2345678901', 'Office B', 'password2'),
(1003, 'Carol Williams', 1, '3456789012', 'Office C', 'password3'),
(1004, 'David Brown', 1, '4567890123', 'Office D', 'password4'),
(1005, 'Eve Davis', 2, '5678901234', 'Office E', 'password5'),
(1006, 'Frank Wilson', 1, '6789012345', 'Office F', 'password6'),
(1007, 'Grace Lee', 1, '7890123456', 'Office G', 'password7'),
(1008, 'Henry Walker', 2, '8901234567', 'Office H', 'password8'),
(1009, 'Ivy Hall', 1, '9012345678', 'Office I', 'password9'),
(1010, 'Jack King', 1, '0123456789', 'Office J', 'password10'),
(1011, 'Karen Scott', 2, '1231231231', 'Office K', 'password11'),
(1012, 'Leo Green', 1, '2342342342', 'Office L', 'password12'),
(1013, 'Mary Young', 1, '3453453453', 'Office M', 'password13'),
(1014, 'Nina Adams', 1, '4564564564', 'Office N', 'password14'),
(1015, 'Oscar Baker', 2, '5675675675', 'Office O', 'password15'),
(1016, 'Paul Carter', 1, '6786786786', 'Office P', 'password16'),
(1017, 'Quinn Evans', 1, '7897897897', 'Office Q', 'password17'),
(1018, 'Rita Foster', 2, '8908908908', 'Office R', 'password18'),
(1019, 'Steve Gray', 1, '9019019019', 'Office S', 'password19'),
(1020, 'Tina Harris', 1, '0120120120', 'Office T', 'password20');
INSERT INTO BookingRecord (SubmissionTime, RoomID, TeacherID, BookingDate, IsApproved) VALUES
('2024-06-01 08:30:00', 1, 1, '2024-07-01', TRUE),
('2024-06-02 09:00:00', 2, 2, '2024-07-02', FALSE),
('2024-06-03 10:00:00', 3, 3, '2024-07-03', TRUE),
('2024-06-04 11:30:00', 4, 4, '2024-07-04', FALSE),
('2024-06-05 12:00:00', 5, 5, '2024-07-05', TRUE),
('2024-06-06 13:30:00', 6, 6, '2024-07-06', FALSE),
('2024-06-07 14:00:00', 7, 7, '2024-07-07', TRUE),
('2024-06-08 15:00:00', 8, 8, '2024-07-08', FALSE),
('2024-06-09 16:00:00', 9, 9, '2024-07-09', TRUE),
('2024-06-10 17:00:00', 10, 10, '2024-07-10', FALSE),
('2024-06-11 08:00:00', 11, 11, '2024-07-11', TRUE),
('2024-06-12 09:30:00', 12, 12, '2024-07-12', FALSE),
('2024-06-13 10:30:00', 13, 13, '2024-07-13', TRUE),
('2024-06-14 11:00:00', 14, 14, '2024-07-14', FALSE),
('2024-06-15 12:30:00', 15, 15, '2024-07-15', TRUE),
('2024-06-16 13:00:00', 16, 16, '2024-07-16', FALSE),
('2024-06-17 14:30:00', 17, 17, '2024-07-17', TRUE),
('2024-06-18 15:30:00', 18, 18, '2024-07-18', FALSE),
('2024-06-19 16:30:00', 19, 19, '2024-07-19', TRUE),
('2024-06-20 17:30:00', 20, 20, '2024-07-20', FALSE);
ALTER DATABASE school CHARACTER SET = utf8mb4 COLLATE = utf8mb4_general_ci;
ALTER TABLE Teacher CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
ALTER TABLE Classroom CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
ALTER TABLE BookingRecord CONVERT TO CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci;
-- 实验室表
CREATE TABLE Lab (
    RoomID INT PRIMARY KEY,
    LabType INT,
    FOREIGN KEY (RoomID) REFERENCES Room(RoomID)
);

-- 多媒体室表
CREATE TABLE MultimediaRoom (
    RoomID INT PRIMARY KEY,
    AirConditioners INT,
    FOREIGN KEY (RoomID) REFERENCES Room(RoomID)
);

-- 录音室表
CREATE TABLE RecordingRoom (
    RoomID INT PRIMARY KEY,
    Cameras INT,
    FOREIGN KEY (RoomID) REFERENCES Room(RoomID)
);
ALTER TABLE Lab
    ADD CONSTRAINT fk_lab_classroom
        FOREIGN KEY (RoomID) REFERENCES classroom(RoomID);
ALTER TABLE MultimediaRoom
    ADD CONSTRAINT fk_multimedia_classroom
        FOREIGN KEY (RoomID) REFERENCES classroom(RoomID);
ALTER TABLE RecordingRoom
    ADD CONSTRAINT fk_recording_classroom
        FOREIGN KEY (RoomID) REFERENCES classroom(RoomID);
ALTER TABLE bookingrecord
    ADD CONSTRAINT fk_booking_classroom
        FOREIGN KEY (RoomID) REFERENCES classroom(RoomID);
use school;
-- 创建实验室类型表
CREATE TABLE IF NOT EXISTS LabType (
                                       LabTypeID INT PRIMARY KEY,
                                       LabTypeName VARCHAR(50)
);

-- 插入实验室类型
INSERT INTO LabType (LabTypeID, LabTypeName)
VALUES
    (1, 'Chemistry'),       -- 化学
    (2, 'Physics'),         -- 物理
    (3, 'Biology'),         -- 生物
    (4, 'ComputerScience'), -- 计算机
    (5, 'Environmental');   -- 水环境

-- 修改 Lab 表，增加 CHECK 约束来限制 LabType 的值
ALTER TABLE Lab
    ADD CONSTRAINT chk_lab_labtype
        CHECK (LabType IN (1, 2, 3, 4, 5));

-- 增加外键约束，确保 LabType 的值在 LabType 表中
ALTER TABLE Lab
    ADD CONSTRAINT fk_lab_labtype1
        FOREIGN KEY (LabType) REFERENCES LabType(LabTypeID);

-- 创建触发器来进一步控制数据的插入或更新
DELIMITER $$

CREATE TRIGGER trg_lab_before_insert
    BEFORE INSERT ON Lab
    FOR EACH ROW
BEGIN
    -- 如果 LabType 不在 1 到 5 之间，则抛出错误
    IF NEW.LabType NOT BETWEEN 1 AND 5 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid LabType. Valid values are 1, 2, 3, 4, and 5.';
    END IF;
END$$

CREATE TRIGGER trg_lab_before_update
    BEFORE UPDATE ON Lab
    FOR EACH ROW
BEGIN
    -- 如果 LabType 不在 1 到 5 之间，则抛出错误
    IF NEW.LabType NOT BETWEEN 1 AND 5 THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Invalid LabType. Valid values are 1, 2, 3, 4, and 5.';
    END IF;
END$$

DELIMITER ;
use school;
ALTER TABLE classroom MODIFY COLUMN RoomNumber VARCHAR(50);
-- 插入数据到 classroom 表
INSERT INTO classroom (RoomID, RoomNumber, RoomName, Capacity, IsOccupied, RoomType) VALUES
                                                                                         (401, 'A101', '普通教室 A101', 30, FALSE, 0),
                                                                                         (402, 'B202', '化学实验室 B202', 25, FALSE, 1),
                                                                                         (403, 'C303', '物理实验室 C303', 20, TRUE, 1),
                                                                                         (404, 'D404', '多媒体教室 D404', 50, FALSE, 2),
                                                                                         (405, 'E505', '录课教室 E505', 15, TRUE, 3);
-- 插入数据到 classroom 表
INSERT INTO lab (RoomID, RoomName, LabType) VALUES
                                                (402, '化学实验室 B202', 1),  -- 化学实验室
                                                (403, '物理实验室 C303', 2);  -- 物理实验室

-- 插入数据到 multimediaroom 表
INSERT INTO multimediaroom (RoomID, RoomName, AirConditioners) VALUES
    (404, '多媒体教室 D404', 2);  -- 有空调

-- 插入数据到 recordingroom 表
INSERT INTO recordingroom (RoomID, RoomName, Cameras) VALUES
    (405, '录课教室 E505', 3);  -- 3 个摄像头
