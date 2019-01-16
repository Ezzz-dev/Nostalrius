function onStepIn(creature, item, position, fromPosition)
	doRelocate({x = 32476, y = 31904, z = 05},{x = 32476, y = 31904, z = 06})
	Game.sendMagicEffect({x = 32476, y = 31904, z = 06}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate({x = 32476, y = 31904, z = 05},{x = 32476, y = 31904, z = 06})
	Game.sendMagicEffect({x = 32476, y = 31904, z = 06}, 11)
end
