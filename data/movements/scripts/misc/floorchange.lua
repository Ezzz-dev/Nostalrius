local list = {
	[293] = {x = 0, y = 0, z = 1},
	[294] = {x = 0, y = 0, z = 1},
	[369] = {x = 0, y = 0, z = 1},
	[370] = {x = 0, y = 0, z = 1},
	[385] = {x = 0, y = 0, z = 1},
	[394] = {x = 0, y = 0, z = 1},
	[411] = {x = 0, y = 0, z = 1},
	[412] = {x = 0, y = 0, z = 1},
	[413] = {x = 0, y = 1, z = 1},
	[414] = {x = 0, y = 1, z = 1},
	[428] = {x = 0, y = 1, z = 1},
	[4823] = {x = 0, y = 1, z = 1},
	[4824] = {x = 0, y = 1, z = 1},
	[4825] = {x = 0, y = 1, z = 1},
	[4826] = {x = 0, y = 1, z = 1},
	[432] = {x = 0, y = 0, z = 1},
	[433] = {x = 0, y = 0, z = 1},
	[434] = {x = 0, y = 1, z = 1},
	[437] = {x = 0, y = 1, z = 1},
	[438] = {x = 0, y = 1, z = 1},
	[451] = {x = 0, y = 1, z = 1},
	[465] = {x = 0, y = -1, z = 1},
	[466] = {x = -1, y = 0, z = 1},
	[467] = {x = 1, y = 0, z = 1},
	[471] = {x = -1, y = -1, z = 1},
	[472] = {x = 1, y = -1, z = 1},
	[473] = {x = -1, y = 1, z = 1},
	[474] = {x = 1, y = 1, z = 1},
	[475] = {x = 0, y = 0, z = 1},
	[476] = {x = 0, y = 0, z = 1},
	[482] = {x = 0, y = 0, z = 1},
	[5081] = {x = 0, y = 0, z = 1},
	[483] = {x = 0, y = 0, z = 1},
	[484] = {x = 0, y = 1, z = 1},
	[485] = {x = 0, y = 1, z = 1},
	[566] = {x = 0, y = 1, z = 1},
	[567] = {x = 1, y = 0, z = 1},
	[594] = {x = 0, y = 0, z = 1},
	[595] = {x = 0, y = 0, z = 1},
	[600] = {x = -1, y = 0, z = 1},
	[601] = {x = 1, y = 0, z = 1},
	[604] = {x = -1, y = 0, z = 1},
	[605] = {x = 1, y = 0, z = 1},
	[607] = {x = 0, y = 0, z = 1},
	[609] = {x = 0, y = 0, z = 1},
	[610] = {x = 0, y = 0, z = 1},
	[615] = {x = 0, y = 0, z = 1},
	[1066] = {x = 0, y = 0, z = 1},
	[1067] = {x = 0, y = 0, z = 1},
	[1080] = {x = 0, y = 0, z = 1},
	[1156] = {x = 0, y = 1, z = 1},
	[1947] = {x = 0, y = -1, z = -1},
	[1950] = {x = 1, y = 0, z = -1},
	[1952] = {x = -1, y = 0, z = -1},
	[1954] = {x = 0, y = 1, z = -1},
	[1956] = {x = 0, y = -1, z = -1},
	[1958] = {x = 0, y = -1, z = -1},
	[1960] = {x = 1, y = 0, z = -1},
	[1962] = {x = -1, y = 0, z = -1},
	[1964] = {x = 0, y = 1, z = -1},
	[1966] = {x = 0, y = -1, z = -1},
	[1969] = {x = 1, y = 0, z = -1},
	[1971] = {x = -1, y = 0, z = -1},
	[1973] = {x = 0, y = 1, z = -1},
	[1975] = {x = 0, y = -1, z = -1},
	[1977] = {x = 0, y = -1, z = -1},
	[1978] = {x = -1, y = 0, z = -1},
	[2192] = {x = -1, y = -1, z = -1},
	[2194] = {x = 1, y = -1, z = -1},
	[2196] = {x = 1, y = 1, z = -1},
	[2198] = {x = -1, y = 1, z = -1},
}

function onStepIn(creature, item, position, fromPosition)
	local entry = list[item:getId()]
	local relPos = item:getPosition():moveRel(entry.x, entry.y, entry.z)
	
	local tile = Tile(relPos)
	if tile == nil or tile:getGround() == nil then
		return false
	end
	
	doRelocate(position, relPos)

	if item:getId() == 293 then
		item:transform(294)
		item:decay()
	elseif item:getId() == 475 then
		item:transform(476)
		item:decay()
	elseif item:getId() == 1066 then
		item:transform(1067)
		item:decay()	
	end
	return true
end

function onAddItem(item, tileitem, position)
	if tileitem:getId() ~= 293 and tileitem:getId() ~= 475 and tileitem:getId() ~= 476 and tileitem:getId() ~= 1066 then
		local entry = list[tileitem:getId()]
		local relPos = tileitem:getPosition():moveRel(entry.x, entry.y, entry.z)
		item:moveTo(relPos)
	end
	return true
end
