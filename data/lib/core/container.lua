function Container.isContainer(self)
	return true
end

function Container.isItem(self)
	return true
end

function Container.isMonster(self)
	return false
end

function Container.isCreature(self)
	return false
end

function Container.isPlayer(self)
	return false
end

function Container.isTeleport(self)
	return false
end

function Container.isTile(self)
	return false
end
